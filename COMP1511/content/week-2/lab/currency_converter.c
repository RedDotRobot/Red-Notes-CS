// Currency Converter
// currency_converter.c
//
// This program was written by Lucas Cheung (z5763342)
// on 26-02-2026
//
// Program that converts AUD to foreign currency

#include <stdio.h>

int main(void) {
	double AUD_amount;
	double currency;

	printf("Enter amount in AUD: ");
	scanf("%lf", &AUD_amount);

	printf("Enter currency (1 = USD, 2 = EUR, 3 = JPY): ");
	scanf("%lf", &currency);

	if (AUD_amount < 1000) {
		if (currency == 1) {
			double converted_amount = 0.65 * AUD_amount;
			printf("%.2lf AUD = %.2lf USD\n", AUD_amount, converted_amount);
		} else if (currency == 2) {
			double converted_amount = 0.6 * AUD_amount;
			printf("%.2lf AUD = %.2lf EUR\n", AUD_amount, converted_amount);
		} else if (currency == 3) {
			double converted_amount = 97.50 * AUD_amount;
			printf("%.2lf AUD = %.2lf JPY\n", AUD_amount, converted_amount);
		}
	} else if (AUD_amount < 5000) {
		if (currency == 1) {
			double converted_amount = 0.65 * AUD_amount;
			double discount = converted_amount * 0.02;
			double discount_amount = converted_amount - discount;
			printf("%.2lf AUD = %.2lf USD\n", AUD_amount, converted_amount);
			printf("Discount: 2%%\n");
			printf("You saved: %.2lf USD\n", discount);
			printf("Discounted total: %.2lf USD \n", discount_amount);
		} else if (currency == 2) {
			double converted_amount = 0.6 * AUD_amount;
			double discount = converted_amount * 0.02;
			double discount_amount = converted_amount - discount;
			printf("%.2lf AUD = %.2lf EUR\n", AUD_amount, converted_amount);
			printf("Discount: 2%%\n");
			printf("You saved: %.2lf EUR\n", discount);
			printf("Discounted total: %.2lf EUR\n", discount_amount);
		} else if (currency == 3) {
			double converted_amount = 97.50 * AUD_amount;
			double discount = converted_amount * 0.02;
			double discount_amount = converted_amount - discount;
			printf("%.2lf AUD = %.2lf JPY\n", AUD_amount, converted_amount);
			printf("Discount: 2%%\n");
			printf("You saved: %.2lf JPY\n", discount);
			printf("Discounted total: %.2lf JPY\n", discount_amount);
		}
	} else {
		if (currency == 1) {
			double converted_amount = 0.65 * AUD_amount;
			double discount = converted_amount * 0.05;
			double discount_amount = converted_amount - discount;
			printf("%.2lf AUD = %.2lf USD\n", AUD_amount, converted_amount);
			printf("Discount: 5%%\n");
			printf("You saved: %.2lf USD\n", discount);
			printf("Discounted total: %.2lf USD\n", discount_amount);
		} else if (currency == 2) {
			double converted_amount = 0.6 * AUD_amount;
			double discount = converted_amount * 0.05;
			double discount_amount = converted_amount - discount;
			printf("%.2lf AUD = %.2lf EUR\n", AUD_amount, converted_amount);
			printf("Discount: 5%%\n");
			printf("You saved: %.2lf EUR\n", discount);
			printf("Discounted total: %.2lf EUR\n", discount_amount);
		} else if (currency == 3) {
			double converted_amount = 97.50 * AUD_amount;
			double discount = converted_amount * 0.05;
			double discount_amount = converted_amount - discount;
			printf("%.2lf AUD = %.2lf JPY\n", AUD_amount, converted_amount);
			printf("Discount: 5%%\n");
			printf("You saved: %.2lf JPY\n", discount);
			printf("Discounted total: %.2lf JPY\n", discount_amount);
		}
	}

	return 0;
}
