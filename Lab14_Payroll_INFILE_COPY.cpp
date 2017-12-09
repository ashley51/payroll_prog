
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
void input_employee_data(std::ifstream &infile, std::string &full_name, double &hours, double &hourly_rate, double &deductions);
std::string join_name(std::string first_name, std::string last_name);
double input_bounded_value(std::string description, double min_value, double max_value);
void split_hours(double hours, double &regular_hours, double &overtime_hours);
double calculate_gross_pay(double regular_hours, double overtime_hours, double hourly_rate);
double calculate_tax(double gross_pay, double tax_rate);
double calculate_net_pay(double gross_pay, double tax, double deductions);
void output_payroll_data(int num_emps, std::string emp_names[], double emp_hours[], double emp_ovtime_hr[],
    double emp_hr_rates[], double emp_grosses[], double emp_taxes[], double emp_deductions[],
    double emp_net_pay[], std::ostream &outfile);
double compute_sum(double data[], int count);
double compute_min(double data[], int count);
double compute_max(double data[], int count);
void output_payroll_summary(int num_emps, std::string emp_names[],
    double emp_grosses[], double total_gross_pay,
    double ave_gross_pay, double min_gross_pay,
    double max_gross_pay, std::ostream &outfile);
void read_data(std::ifstream &infile, std::string &first_name, std::string &last_name, 
    double &hours, double &hourly_rate, double &deductions);

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
                ave_gross_pay,
                min_gross_pay,
                max_gross_pay,
                emp_grosses[MAX_EMPS],
                emp_hours[MAX_EMPS],
                emp_ovtime_hr[MAX_EMPS],
                emp_hr_rates[MAX_EMPS],
                emp_taxes[MAX_EMPS],
                emp_deductions[MAX_EMPS],
                emp_net_pay[MAX_EMPS];

    int         i,
                num_emps;
//    char        answer;
    std::ofstream outfile;                  // OUTFILE VARIABLE
    std::ifstream infile;                   // INFILE VARIABLE

    std::cout << std::fixed << std::setprecision(2);

    total_gross_pay = 0;
    num_emps = 0;

    // WELCOME MESSAGE //
    welcome_message();

        infile.open("f:\\CISP 301\\I.O Files\\empdata.txt");                        // INFILE LINE
        if (!infile.is_open())
        {
            std::cout << "Unable to open input file!" << std::endl;
            exit(EXIT_FAILURE);
        }

        outfile.open("f:\\CISP 301\\I.O Files\\empdata_report.txt");                 // OUTFILE LINE
        if (!outfile.is_open())
        {
            std::cout << "Unable to open output file!" << std::endl;
            exit(EXIT_FAILURE);
        }
    read_data(infile, first_name, last_name, hours, hourly_rate, deductions);     //READ DATA

    outfile << "                                          "
            << "                                  " << std::endl;
    outfile << "                      Reg.   Ovt.   Hourly"
            << "  Gross                    Net    " << std::endl;
    outfile << "Name                  Hours  Hours  Rate  "
            << "  Pay      Taxes   Deduct  Pay    " << std::endl;
    outfile << "====================  =====  =====  ======"
            << "  =======  ======  ======  =======" << std::endl;

    while (!infile.eof())
    {
        full_name = last_name + ", " + first_name;

        // PROCESSING 
        split_hours(hours, regular_hours, overtime_hours);
        gross_pay = calculate_gross_pay(regular_hours, overtime_hours, hourly_rate);
        tax = calculate_tax(gross_pay, TAX_RATE);
        net_pay = calculate_net_pay(gross_pay, tax, deductions);

        std::cout << "Employee name is  " << full_name << std::endl;
        std::cout << "Hours worked:     " << hours << std::endl;
        std::cout << "Hourly rate is:   " << hourly_rate << std::endl;
        std::cout << "Deduction is :    " << deductions << std::endl;
        std::cout << std::endl;

        outfile << std::left << std::setw(20) << full_name << "  ";
        outfile << std::right;
        outfile << std::fixed << std::setprecision(2) << std::setw(5) << hours << "  ";
        outfile << std::setw(5) << overtime_hours << "  ";
        outfile << std::setw(6) << hourly_rate << "  ";
        outfile << std::setw(7) << gross_pay << "  ";
        outfile << std::setw(6) << tax << "  ";
        outfile << std::setw(6) << deductions << "  ";
        outfile << std::setw(7) << net_pay << std::endl << std::endl;

        read_data(infile, first_name, last_name, hours, hourly_rate, deductions);       // READ NEXT DATA
        for (i = 0; i < num_emps; i++)
        {
        outfile << std::left << std::setw(20) << emp_names[i] << "  "
            << std::right << std::setw(8) << emp_grosses[i]
            << std::endl;
        }
    }

    do {
        // INPUT SECTION //
        input_employee_data(infile, full_name, hours, hourly_rate, deductions);
        // PROCESSING SECTION //
        split_hours(hours, regular_hours, overtime_hours);
        gross_pay = calculate_gross_pay(regular_hours, overtime_hours, hourly_rate);
        tax = calculate_tax(gross_pay, TAX_RATE);
        net_pay = calculate_net_pay(gross_pay, tax, deductions);
        // COUNTER AND ACCUMULATOR
        emp_names[num_emps] = full_name;
        emp_grosses[num_emps] = gross_pay;
        emp_hours[num_emps] = regular_hours;
        emp_ovtime_hr[num_emps] = overtime_hours;
        emp_hr_rates[num_emps] = hourly_rate;
        emp_taxes[num_emps] = tax;
        emp_deductions[num_emps] = deductions;
        emp_net_pay[num_emps] = net_pay;
        total_gross_pay = total_gross_pay + gross_pay;
        num_emps++;
    } while (num_emps < MAX_EMPS); 
    std::cout << std::endl;
    if (num_emps > 0)
    {
        total_gross_pay = compute_sum(emp_grosses, num_emps);
        ave_gross_pay = total_gross_pay / num_emps;
        min_gross_pay = compute_min(emp_grosses, num_emps);
        max_gross_pay = compute_max(emp_grosses, num_emps);
    }
    else
    {
        total_gross_pay = 0;
        ave_gross_pay   = 0;
        min_gross_pay   = 0;
        max_gross_pay   = 0;
    }
    output_payroll_summary(num_emps, emp_names, emp_grosses, total_gross_pay,
        min_gross_pay, ave_gross_pay, max_gross_pay, outfile);

    outfile.close();            // ADDED LINE FOR OUTFILE
    infile.close();

    system("pause");
    return 0;
}
//===============================================================================================//
//==========================FUNCTIONS/PROCEDURES=================================================//
//===============================================================================================//
//void sort_employees(num_emps[])

void read_data(std::ifstream &infile, std::string &first_name, std::string &last_name, double &hours, double &hourly_rate, double &deductions)
{
    infile >> first_name >> last_name >> hours >> hourly_rate >> deductions;
}
// DISPLAY RESULTS FROM DATA OF GIVEN EMPLOYEE
void output_payroll_data(int num_emps, std::string emp_names[], double emp_hours[], double emp_ovtime_hr[],
    double emp_hr_rates[], double emp_grosses[], double emp_taxes[], double emp_deductions[],
    double emp_net_pay[], std::ostream &outfile)
{
    int i;

    outfile << "                                          "
            << "                                  " << std::endl;
    outfile << "                      Reg.   Ovt.   Hourly"
            << "  Gross                    Net    " << std::endl;
    outfile << "Name                  Hours  Hours  Rate  "
            << "  Pay      Taxes   Deduct  Pay    " << std::endl;
    outfile << "====================  =====  =====  ======"
            << "  =======  ======  ======  =======" << std::endl;
    for (i = 0; i < num_emps; i++)
    {
        outfile << std::left << std::setw(20) << emp_names[i] << "  ";
        outfile << std::right;
        outfile << std::fixed << std::setprecision(2) << std::setw(5) << emp_hours[i] << "  ";
        outfile << std::setw(5) << emp_ovtime_hr[i] << "  ";
        outfile << std::setw(6) << emp_hr_rates[i] << "  ";
        outfile << std::setw(7) << emp_grosses[i] << "  ";
        outfile << std::setw(6) << emp_taxes[i] << "  ";
        outfile << std::setw(6) << emp_deductions[i] << "  ";
        outfile << std::setw(7) << emp_net_pay[i] << std::endl << std::endl;
    }
}
// OUTPUT MODULE TO DISPLAY A TABLE
void output_payroll_summary(int num_emps, std::string emp_names[],
    double emp_grosses[], double total_gross_pay, double ave_gross_pay,
    double min_gross_pay, double max_gross_pay, std::ostream &outfile)
{
    int i;

    std::cout << std::endl << std::endl << std::endl;
    std::cout << "                              " << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout << "   Employee Payroll Summary   " << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout << std::endl;
    std::cout << "                       Gross  " << std::endl;
    std::cout << "Name                   Pay    " << std::endl;
    std::cout << "=====================  =======" << std::endl;
    /////////////////////////////////////////////////////////////
    for (i = 0; i < num_emps; i++)
    {
        std::cout << std::left << std::setw(20) << emp_names[i] << "  "
            << std::right << std::setw(8) << emp_grosses[i]
            << std::endl;
    }
    ////////////////////////////////////////////////////////////
    outfile << std::endl;
    std::cout << "Total gross pay    : $" << std::setw(8) << total_gross_pay << std::endl;
    std::cout << "Average gross pay  : $" << std::setw(8) << ave_gross_pay << std::endl;
    std::cout << "Minimum gross pay  : $" << std::setw(8) << min_gross_pay << std::endl;
    std::cout << "Maximum gross pay  : $" << std::setw(8) << max_gross_pay << std::endl;
}
// WELCOME MESSAGE
void welcome_message()
{
    std::cout << "Running Payroll Program LAB15" << std::endl << std::endl;
}
// INPUT MODULE THAT READS THE EMPLOYEE'S NAME, WORKING HOURS AND PAY RATE.
void input_employee_data(std::ifstream &infile,std::string &full_name, double &hours, double &hourly_rate, double &deductions)
{
    std::string     first_name,
                    last_name;
    infile >> first_name;
    infile >> last_name;
    infile >> hours;
    infile >> hourly_rate;
    infile >> deductions;

    full_name = join_name(first_name, last_name);
}
// JOIN NAME
std::string join_name(std::string first_name, std::string last_name)
{
    std::string full_name;

    full_name = last_name + ", " + first_name;
    return full_name;
}
// CALCULATE GROSS PAY
double calculate_gross_pay(double regular_hours, double overtime_hours, double hourly_rate)
{
    double gross_pay;

    gross_pay = (regular_hours * hourly_rate) +
        (overtime_hours * hourly_rate * OVERTIME_RATE);
    return gross_pay;
}
// SPLIT HOURS 
void split_hours(double hours, double &regular_hours, double &overtime_hours)
{
    if (hours <= REGULAR_HOURS_LIMIT)
    {
        regular_hours = hours;
        overtime_hours = MIN_HOURS;
    } 
    else 
    {
        regular_hours = REGULAR_HOURS_LIMIT;
        overtime_hours = hours - REGULAR_HOURS_LIMIT;
    }
}
// CALCULATE TAX
double calculate_tax(double gross_pay, double tax_rate)
{
    double tax;

    tax = gross_pay * tax_rate;
    return tax;
}
// CALCULATE NET PAY
double calculate_net_pay(double gross_pay, double tax, double deductions)
{
    double net_pay;

    net_pay = gross_pay - tax - deductions;
    return net_pay;
}
// FUNCTION MODULE TO CALCULATE WORKING HOURS
double input_bounded_value(std::string description, double min_value, double max_value)
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