# Employee Payroll System

A menu-driven C++ console application for managing employees, recording attendance, and generating basic payslips. It supports full-time, part-time, and contract employees.

## Features

- Add employees with a unique ID, name, department, employee type, and salary rate
- View and search employee records
- Record attendance in days and hours
- Generate a payslip with basic salary, allowance, deduction, and net salary
- Save employee details to `employees.txt`
- Append generated payslip totals to `payroll.txt`

## Salary Calculation

The application calculates basic salary according to employee type:

- **Full-time:** salary rate ÷ 30 × days present
- **Part-time:** salary rate × hours worked
- **Contract:** salary rate × days present

Payslips include a 10% allowance and a 5% deduction based on basic salary.

## Requirements

- A C++ compiler, such as g++
- Standard C++ libraries

## Build and Run

### Windows (g++)

```bash
g++ HCL_Project.cpp -o payroll.exe
payroll.exe
```

### Linux or macOS

```bash
g++ HCL_Project.cpp -o payroll
./payroll
```

## Data Files

- `employees.txt` is overwritten when employee data is saved. It stores each employee's ID, name, department, and type.
- `payroll.txt` is appended to when a payslip is generated. It stores the employee ID and net salary.

These files are created in the program's current working directory.

## Notes

- Employee and attendance data are held in memory while the program runs. Employee details are saved to a file, but the application does not currently load them from that file when it starts.
- Names and departments are entered as single words.
- Salary rates should be entered using the units appropriate for the selected employee type.

## License

No license specified.
