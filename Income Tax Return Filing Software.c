#include <stdio.h>

int main() {
    
    double ctc, basicsal, hra, epf, ccpf, gratuity, pt, sd,max_ded_under_sec_80c;
    double sda, idd, allowances, gros3al, hrpm, v2, v3, minval;
    double hlrp, lohp, hlbnft, ded_under_sec_80c, cetf, lic, exp_on_medicine, bonus;
    double ti, it, ec, dd, netsal;
	char q1,q2,q3,q4,q5;

    // Input
    printf("Enter Your Cost To Company (CTC) : ");
    scanf("%lf", &ctc);

    // Calculations
    basicsal = (ctc * 40) / 100;
    hra = (basicsal * 50) / 100;
    epf = (basicsal * 12) / 100;
    ccpf = (basicsal * 12) / 100;
    gratuity = (basicsal * 4.81) / 100;
    pt = 2500;
    sd = 50000;

    printf("Basic Salary : %lf pa\n", basicsal);
    printf("HRA : %lf pa\n", hra);
    printf("Fixed Salary : %lf pa\n", (basicsal + hra));
    printf("Employee PF : %lf pa\n", epf);
    printf("Employer / Company PF : %lf pa\n", ccpf);
    printf("Gratuity : %lf pa\n", gratuity);
    printf("Professional / Employment Tax : %lf pa\n", pt);

    printf("Have you declared anything against allowances (Y/N) : ");
    scanf(" %c", &q1);
    sda = 0;

    if (q1 == 'Y' || q1 == 'y') {
        printf("Enter an amount that you declared against allowances : ");
        scanf("%lf", &sda);
    }

    // Conveyance Allowances, LTA, Telephone Expenses Allowances, Children Education Allowances, Professional Pursuit Allowances
    // Indirect deductions
    idd = ccpf + gratuity + sda;
    allowances = ctc - (basicsal + hra + idd);
    gros3al = basicsal + hra + allowances;

    printf("Gross Sal : %lf pa\n", gros3al);
    printf("Gross Sal : %lf pm\n", (gros3al / 12));

    // Exempted u/s 10
    printf("Enter house rent paid by you per month : ");
    scanf("%lf", &hrpm);
    printf("Actual HRA Received : %lf pa <===V1\n", hra);
    printf("Actual Rent Paid : %lf pa\n", (hrpm * 12));
    v2 = (hrpm * 12) - ((basicsal * 10) / 100);
    printf("Actual Rent Paid - 10% of Basic Sal : %lf <===V2\n", v2);
    v3 = hra;
    printf("Are you living in a metro city (Y/N) : ");
    scanf(" %c", &q2);

    if (q2 == 'N' || q2 == 'n') {
        v3 = (basicsal * 40) / 100;
    }

    printf("50% (Metro Cities) / 40% (Other Cities) of Basic Sal : %lf <===V3\n", v3);

    minval = 0;

    if (hra <= v2 && hra <= v3) {
        minval = hra;
    } else if (v2 <= hra && v2 <= v3) {
        minval = v2;
    } else if (v3 <= hra && v3 <= v2) {
        minval = v3;
    }

    printf("Min. of v1, v2, v3 : %lf <=== Exempted u/s 10\n", minval);

    // Deductions u/s 80C
    printf("Do you have any house loan (Y/N) : ");
    scanf(" %c", &q3);

    hlrp = 0;
    lohp = 0;
    hlbnft = 0;

    if (q3 == 'Y' || q3 == 'y') {
        printf("Enter house loan repayment for the year : ");
        scanf("%lf", &hlrp);
        printf("Enter loss on house property for the year : ");
        scanf("%lf", &lohp);

        if (lohp >= 200000) {
            lohp = 200000;
        }

        printf("Is it your first property (Y/N) : ");
        scanf(" %c", &q4);

        // Deductions u/s 80EE
        if (q4 == 'Y' || q4 == 'y') {
            hlbnft = 50000;  // Additional house loan benefit
        }
    }

    max_ded_under_sec_80c = 150000;
    ded_under_sec_80c = 0;

    printf("Enter an amount that you spend for children education tuition fee in the current year : ");
    scanf("%lf", &cetf);
    printf("Enter an amount that you spend for LIC in the current year : ");
    scanf("%lf", &lic);

    ded_under_sec_80c = cetf + lic + hlrp + epf;

    if (max_ded_under_sec_80c < ded_under_sec_80c) {
        ded_under_sec_80c = max_ded_under_sec_80c;
    }

    printf("Deductions u/s 80C : %lf\n", ded_under_sec_80c);

    // Deductions u/s 80DSI
    exp_on_medicine = 0;
    printf("Have you spent anything for medicine in current year (Y/N) : ");
    scanf(" %c", &q5);

    if (q5 == 'Y' || q5 == 'y') {
        printf("Enter medical insurance - self / spouse / children (60 <years) - with insurance, if you have any up to 25K pa : ");
        scanf("%lf", &exp_on_medicine);

        if (exp_on_medicine > 25000) {
            exp_on_medicine = 25000;
        }
    }

    // Incentives Section
    printf("Please enter if you got any bonus in the current year : ");
    scanf("%lf", &bonus);

    // Taxable Income
    ti = (gros3al + bonus) - (minval + sd + pt + lohp + hlbnft + ded_under_sec_80c + exp_on_medicine);

    printf("Taxable Income : %lf\n", ti);

    // Income Tax Calculation Area

    // Income Tax Calculation
    it = 0.0;
    if (ti > 500000 && ti <= 1000000) {
        it = ((ti - 500000) * 20) / 100;
        it = it + 12500;
    } else if (ti > 1000000) {
        it = ((ti - 1000000) * 30) / 100;
        it = it + 100000 + 12500;
    }

    // Educational Cess - 4% of Income Tax
    ec = (it * 4) / 100;
    it = it + ec;

    printf("Income Tax On Taxable Income: %.2lf is %.2lf pa\n", ti, it);

    // Direct Deductions
    dd = epf + pt + it;
    printf("Direct Deductions: %.2lf pa\n", dd);

    // Net Salary Calculation
    netsal = (gros3al + bonus) - (epf + pt + it);
    printf("Net Sal: %.2lf pa\n", netsal);
    printf("Net Sal: %.2lf pm\n", netsal / 12);
    
    return 0;
}
