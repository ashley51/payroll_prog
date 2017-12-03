
#include <iomanip>
#include <iostream>
#include <string>

#define MIN_HOURS                0.00   // minimum hours per week
#define MAX_HOURS               60.00   // maximum hours per week
#define MIN_RATE                 0.00   // minimum pay rate
#define MAX_RATE                99.99   // maximum pay rate
#define REGULAR_HOURS_LIMIT     40.00   // hours at which overtime begins
#define OVERTIME_RATE            1.50   // overtime pay rate
#define TAX_RATE                 0.30   // tax rate at 30%
#define PARKING_RATE            10.00   // perking rate deduction
#define TRANSIT_RATE             5.00   // transit rate deduction
#define ZERO_DEDUCTION           0.00   // zero deduction


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
void get_yesno (std::string question, char &answer);   


int main()
{
    std::string first_name,             // employee's first name
                last_name,              // employee's last name
                full_name;              // employee's concatenated full name

    double      hours,                  // number of hours worked
                regular_hours,          // number of regular work hours
                overtime_hours,         // number of overtime work hours
                hourly_rate,            // hourly pay rate
                gross_pay,              // employee's gross pay
                net_pay,                // employee's net pay
                tax,                    // employee's tax amount
                total_gross_pay,        // accumulated gross pay
                deductions,             // monthly pay deductions
                average;

    int         emp_count;              // employee count being processed   

    char        answer;                 // user's yes or no response

    std::cout << std::fixed << std::setprecision(2);

    total_gross_pay = 0;
    emp_count = 0;
    average = 0;
   
    // WELCOME MESSAGE //
    welcome_message();
    
    do { 
        // INPUT SECTION //
        input_employee_data (full_name, hours, hourly_rate, deductions);

        // PROCESSING SECTION //
        split_hours (hours, regular_hours, overtime_hours);
        gross_pay = calculate_gross_pay (regular_hours, overtime_hours, hourly_rate); 
        tax = calculate_tax (gross_pay, TAX_RATE);      
        net_pay = calculate_net_pay (gross_pay, tax, deductions);
  
        // OUTPUT SECTION //
        output_payroll_data (full_name, regular_hours, overtime_hours, hourly_rate, gross_pay, 
                             tax, deductions, net_pay);

        // PROCESS ANOTHER EMPLOYEE ?
        get_yesno ("Process another employee", answer);
        std::cout << std::endl;

        // COUNTER AND ACCUMULATOR
        total_gross_pay = total_gross_pay + gross_pay;
        emp_count++;
        // ============================================
        
        

    } while (answer == 'Y'); 
   
   
    // OUTPUT SUMMARY
    std::cout << std::endl;
    std::cout << "Employees processed: " << emp_count << std::endl;
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


    system ("pause");

    return 0;
} 
//===============================================================================================//
//==========================PROCEDURES=SECTION===================================================//
//===============================================================================================//

// WELCOME MESSAGE
void welcome_message()
{
    std::cout << "Running Payroll Program LAB12 Ver.b " << std::endl << std::endl;
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
    if (hours <= REGULAR_HOURS_LIMIT) {
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

// GET A YESNO RESPONSE IF TO CONTINUE THE WHOLE PROCESS AGAIN
void get_yesno (std::string question, char &answer)
{
    do {
        std::cout << std::endl;
        std::cout << question << " (Y/N)? ";
        std::cin >> answer;

        // CONVERT LOWER-CASE TO UPPERCASE
        if (answer == 'y') {
            answer = 'Y';
        } else if (answer == 'n') {
                   answer = 'N';
        }
        if (answer != 'Y' && answer != 'N') {
            std::cout << "Please press 'Y' for yes or 'N' for no."
                      << std::endl << std::endl;
        }
    } while (answer != 'Y' && answer != 'N');
}

// DEDUCTIONS MODULE TO CLASSIFY THE DEDUCTION AMOUNT
double get_deductions (std::string question)
{   
    char    answer;

    double  deductions;

    do {
        get_yesno ("Does the employee use the Parking Garage?", answer);
        if (answer == 'Y') {
            deductions = PARKING_RATE;
        } else if (answer == 'N') {
            get_yesno ("Does the employee participate in the transit program", answer);
            deductions = TRANSIT_RATE;
        } 
        if (answer == 'N') {
            deductions = ZERO_DEDUCTION;
        }
    } while (answer != 'Y' && answer != 'N');

    return  deductions;
}

// FUNCTION MODULE TO CALCULATE WORKING HOURS
double input_bounded_value (std::string description, double min_value, double max_value) 
{
    double value;

    do {
        std::cout << "Enter the " << description;
        std::cin >> value;
        if (value < min_value || value > max_value) {
            std::cout << "The number of working hours must be "
                << " between " << min_value << " and "
                << max_value << std::endl << std::endl;
        }
    } while (value < min_value || value > max_value);

    return value;
}