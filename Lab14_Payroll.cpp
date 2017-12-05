// Program      : lab14
// Author       : James Bartolome
// Due Date     : November 20, 2017
// Description  : The Supermarket payroll program conversion from pseudocode to
//                C/C++ code with the utilization of procedures to achieve a
//                more simple and cleaner line of coding.
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#define MAX_EMPS                   10      // MAX NUMBER OF EMPLOYEES
#define MIN_HOURS                0.00   
#define MAX_HOURS               60.00   
#define MIN_RATE                 0.00   
#define MAX_RATE                99.99   
#define REGULAR_HOURS_LIMIT     40.00   
#define OVERTIME_RATE            1.50   
#define TAX_RATE                 0.30   
#define PARKING_RATE            10.00   
#define TRANSIT_RATE             5.00   
#define ZERO_DEDUCTION           0.00   


void welcome_message();
void input_employee_data (std::string &full_name, double &hours, double &hourly_rate, double &deductions);
std::string join_name (std::string first_name, std::string last_name);
double input_bounded_value (std::string description, double min_value, double max_value);
void split_hours (double hours, double &regular_hours, double &overtime_hours);
double get_deductions (std::string question);
double calculate_gross_pay (double regular_hours, double overtime_hours, double hourly_rate);
double calculate_tax (double gross_pay, double tax_rate);
double calculate_net_pay (double gross_pay, double tax, double deductions);
void output_payroll_data (std::string full_name, double regular_hours, double overtime_hours,
                          double hourly_rate, double gross_pay, double tax, double deductions,
                          double net_pay);
char get_yesno (std::string question); 
void output_brief_summary(int num_emps, double total_gross_pay);
double compute_sum(double data[], int count);
double compute_min(double data[], int count);
double compute_max(double data[], int count);
void output_payroll_summary(int num_emps, std::string emp_names[],
                            double emp_grosses[], double total_gross_pay, 
                            double ave_gross_pay, double min_gross_pay, 
                            double max_gross_pay);

int main()
{
    std::string emp_names[MAX_EMPS],        //
                first_name,             
                last_name,              
                full_name;              
    double      hours,                  
                regular_hours,          
                overtime_hours,         
                hourly_rate,            
                gross_pay,              
                net_pay,                
                tax,                    
                total_gross_pay,        
                deductions,
                ave_gross_pay,              //
                min_gross_pay,              //
                max_gross_pay,              //
                emp_grosses[MAX_EMPS];      //
    int         num_emps;            
    char        answer; 
    std::ofstream outfile;                  //

    std::cout << std::fixed << std::setprecision(2);

    total_gross_pay = 0;
    num_emps = 0;  

    // WELCOME MESSAGE //
    welcome_message();

        outfile.open("f:\\CISP 301\\emp_data.txt");                 // ADDED
        if (!outfile.is_open())
        {
            std::cout << "Unable to open output file" << std::endl;
            exit(EXIT_FAILURE);
        }
    
    do { 
        // INPUT SECTION //
        input_employee_data (full_name, hours, hourly_rate, deductions);

        // PROCESSING SECTION //
        split_hours (hours, regular_hours, overtime_hours);
        gross_pay = calculate_gross_pay (regular_hours, overtime_hours, hourly_rate); 
        tax = calculate_tax (gross_pay, TAX_RATE);      
        net_pay = calculate_net_pay (gross_pay, tax, deductions);
  
        // OUTPUT SECTION //
        output_payroll_data (full_name, regular_hours, overtime_hours, 
                             hourly_rate, gross_pay, tax, deductions, net_pay);

        // COUNTER AND ACCUMULATOR
        emp_names[num_emps] = full_name;
        emp_grosses[num_emps] = gross_pay;
        total_gross_pay = total_gross_pay + gross_pay;
        num_emps++;

    } while (num_emps < MAX_EMPS &&
             get_yesno("Process another employee") == 'Y'); 

    // DISPLAY BRIEF SUMMARY
    // output_brief_summary(num_emps, total_gross_pay);  // DUPLICATE

    if (num_emps > 0) 
    {
        total_gross_pay = compute_sum(emp_grosses, num_emps);
        ave_gross_pay = total_gross_pay / num_emps;
        min_gross_pay = compute_min(emp_grosses, num_emps);
        max_gross_pay = compute_max(emp_grosses, num_emps);
    } else 
    {
        total_gross_pay = 0;
        ave_gross_pay   = 0;
        min_gross_pay   = 0;
        max_gross_pay   = 0;
    }
    output_payroll_summary(num_emps, emp_names, emp_grosses, total_gross_pay,
                           min_gross_pay, ave_gross_pay, max_gross_pay);
    std::cout << std::endl;

    outfile.close();            // ADDED
    
    system ("pause");
    return 0;
} 
//===============================================================================================//
//==========================FUNCTIONS/PROCEDURES=================================================//
//===============================================================================================//
// WELCOME MESSAGE
void welcome_message()
{
    std::cout << "Running Payroll Program LAB14" << std::endl << std::endl;
}
// INPUT MODULE THAT READS THE EMPLOYEE'S NAME, WORKING HOURS AND PAY RATE.
void input_employee_data (std::string &full_name, double &hours, double &hourly_rate, double &deductions)
{   
    std:: string    first_name,
                    last_name;

    std::cout << std::endl;
    std::cout << "Enter employee's first name: ";
    std::cin >> first_name;
    std::cout << "Enter employee's last name: ";
    std::cin >> last_name;

    full_name = join_name(first_name, last_name);

    hours = input_bounded_value ("number of hours worked: ", MIN_HOURS, MAX_HOURS);

    hourly_rate = input_bounded_value ("hourly pay rate: ", MIN_RATE, MAX_RATE);

    deductions = get_deductions ("Does the employee use the Parking Garage");
}
// JOIN NAME - concatenate first_name and last_name to full_name.
std::string join_name(std::string first_name, std::string last_name)
{   
    std::string full_name;

    full_name = last_name + ", " + first_name;

    return full_name;
}
// CALCULATE GROSS PAY
double calculate_gross_pay (double regular_hours, double overtime_hours, double hourly_rate)
{   
    double gross_pay;

    gross_pay = (regular_hours * hourly_rate) + 
                (overtime_hours * hourly_rate * OVERTIME_RATE);

    return gross_pay;
}
// SPLIT HOURS - split the working hours input into regular_hours or overtime_hours
void split_hours (double hours, double &regular_hours, double &overtime_hours)
{
    if (hours <= REGULAR_HOURS_LIMIT) 
        {
            regular_hours = hours;
            overtime_hours = MIN_HOURS;
        } else {
            regular_hours = REGULAR_HOURS_LIMIT;
            overtime_hours = hours - REGULAR_HOURS_LIMIT;
        }
}
// CALCULATE TAX
double calculate_tax (double gross_pay, double tax_rate)
{   
    double tax;

    tax = gross_pay * tax_rate;

    return tax;
}
// CALCULATE NET PAY
double calculate_net_pay (double gross_pay, double tax, double deductions)
{
    double net_pay;

    net_pay = gross_pay - tax - deductions;

    return net_pay;
}
// DISPLAY RESULTS FROM DATA OF GIVEN EMPLOYEE
void output_payroll_data (std::string full_name, double regular_hours, double overtime_hours,
                          double hourly_rate, double gross_pay, double tax, double deductions,
                          double net_pay)
{
        std::cout << std::endl;
        std::cout << "12345678901234567890##21.00##21.00##321.00"
                  << "##4321.00##321.00##321.00##4321.00" << std::endl;
        std::cout << "                      Reg.   Ovt.   Hourly"
                  << "  Gross                    Net    " << std::endl;
        std::cout << "Name                  Hours  Hours  Rate  "
                  << "  Pay      Taxes   Deduct  Pay    " << std::endl;
        std::cout << "====================  =====  =====  ======"
                  << "  =======  ======  ======  =======" << std::endl;
        std::cout << std::left << std::setw(20) << full_name << "  ";
        std::cout << std::right;
        std::cout << std::setw(5) << regular_hours << "  ";
        std::cout << std::setw(5) << overtime_hours << "  ";
        std::cout << std::setw(6) << hourly_rate << "  ";
        std::cout << std::setw(7) << gross_pay << "  ";
        std::cout << std::setw(6) << tax << "  ";
        std::cout << std::setw(6) << deductions << "  ";
        std::cout << std::setw(7) << net_pay << std::endl << std::endl;
}
// OUTPUT MODULE TO DISPLAY A TABLE
void output_payroll_summary(int num_emps, std::string emp_names[],
    double emp_grosses[], double total_gross_pay, double ave_gross_pay,
    double min_gross_pay, double max_gross_pay)
{
    int i;

    std::cout << std::endl;
    std::cout << "Employees processed: " << num_emps << std::endl;
    std::cout << "Total gross pay: $" << total_gross_pay << std::endl;
    std::cout << std::endl << std::endl << std::endl;
    std::cout << "12345678901234567890##54321.00" << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout << "   Employee Payroll Summary   " << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout << std::endl;
    std::cout << "                       Gross  " << std::endl;
    std::cout << "Name                   Pay    " << std::endl;
    std::cout << "=====================  =======" << std::endl;

    for (i = 0; i < num_emps; i++)
    {
        std::cout << std::left << std::setw(20) << emp_names[i] << "  "
            << std::right << std::setw(8) << emp_grosses[i]
            << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Total gross pay    : $" << std::setw(8) << total_gross_pay << std::endl;
    std::cout << "Average gross pay  : $" << std::setw(8) << ave_gross_pay << std::endl;
    std::cout << "Minimum gross pay  : $" << std::setw(8) << min_gross_pay << std::endl;
    std::cout << "Maximum gross pay  : $" << std::setw(8) << max_gross_pay << std::endl;
}
// GET A YESNO RESPONSE IF TO CONTINUE THE WHOLE PROCESS AGAIN
char get_yesno (std::string question)
{   
    char answer;
    do {
        std::cout << std::endl;
        std::cout << question << " (Y/N)? ";
        std::cin >> answer;

        // CONVERT LOWER-CASE TO UPPERCASE
        answer = toupper(answer);
        if (answer != 'Y' && answer != 'N') 
        {
            std::cout << "Please press 'Y' for yes or 'N' for no."
                      << std::endl << std::endl;
        }
    } while (answer != 'Y' && answer != 'N');
    return answer;
}
// DEDUCTIONS MODULE TO CLASSIFY THE DEDUCTION AMOUNT
double get_deductions (std::string question)
{   
    double  deductions;    
        
        if (get_yesno("Does the employee use the parking garage") == 'Y') 
        {
            deductions = PARKING_RATE;
        } 
        else if (get_yesno("Does the employee participate in the transit program") == 'Y')
        {
            deductions = TRANSIT_RATE;
        } 
        else
        {
            deductions = ZERO_DEDUCTION;
        }
    
    return  deductions;
}
// FUNCTION MODULE TO CALCULATE WORKING HOURS
double input_bounded_value (std::string description, double min_value, double max_value) 
{
    double value;

    do 
    {
        std::cout << "Enter the " << description;
        std::cin >> value;
        if (value < min_value || value > max_value) 
        {
            std::cout << "The number of working hours must be "
                << " between " << min_value << " and "
                << max_value << std::endl << std::endl;
        }
    } while (value < min_value || value > max_value);

    return value;
}
// DISPLAYS THE BRIEF SUMMARY; TOTAL GROSS and EMPLOYEES PROCESSED
void output_brief_summary(int num_emps, double total_gross_pay)
{
    std::cout << std::endl;
    std::cout << "Employees processed: " << num_emps << std::endl;
    std::cout << "Total gross pay: $" << total_gross_pay << std::endl;
}
// COMPUTES SUM OF GIVEN ARRAY DATA
double compute_sum(double data[], int count)
{
    double sum = 0;
    int i;

    for (i = 0; i < count; i++) 
    {
        sum = sum + data[i];
    }
    return sum;
}
// COMPUTE MIN VALUE OF GIVEN ARRAY
double compute_min(double data[], int count)
{
    double min;
    int i;

    min = data[0];
    for (i = 1; i < count; i++) 
    {
        if (data[i] < min) 
        {
            min = data[i];
        }
    }
    return min;
}
// COMPUTE MAX VALUE OF GIVEN ARRAY
double compute_max(double data[], int count)
{
    double max;
    int i;

    max = data[0];
    for (i = 1; i < count; i++)
    {
        if (data[i] > max) 
        {
            max = data[i];
        }
    }
    return max;
}