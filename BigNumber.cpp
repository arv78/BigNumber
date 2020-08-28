#include <iostream>
#include <cmath>
using namespace std;

class numbers {
private:
	int sizef;
	int * value1;
	int si_num;
	int decimal;
public:
	numbers() {
		sizef = 1;
		value1 = new int[100000];
		value1[0] = 0;
		si_num = 1;
		decimal = 0;
	}
	numbers(char *x)
	{
		decimal = 0;
		si_num = 1;
		if (x[0] == '-') {
			x = x + 1;
			si_num = 0;
		}
		sizef = strlen(x);
		int h = sizef;
		
		for (int i = 0; i < sizef; i++)
			if (x[i] == '.')
				sizef = sizef - 1;
		int flag = 0;
		while (x[h] != '.'&&flag == 0) {
			decimal++;
			h--;
			if (h == 0) {
				decimal = 0;
				flag = 1;
			}	
		}
		decimal = decimal - 1;
		if (decimal == -1) {
			decimal = 0;
		}
		cout << decimal<<endl;

		for (int j = 0; j < sizef; j++) {
			if (x[j] == '.')
				strcpy(x + j, x + j + 1);
		}

		value1 = new int[sizef];
		for (int i = 0; i < sizef; i++) {
			value1[i] = x[i] - '0';
		}

		/*for (int i = 0; i < sizef; i++)
			cout << value1[i];
		cout << endl;
		cout << sizef << endl;*/
	}
	numbers(int * x, int size) {
		sizef = size;
		value1 = new int[size];
		for (int i = 0; i < size ; i++)
			value1[i] = x[i];
		si_num = 1;
		decimal = 0;
	}
	/*int get_size_int(int *arr) {
		int size;
		size = sizeof(arr) / sizeof(arr[0]);
		return size;
	}*/
	void reverse() {
		for (int i = 0; i < (sizef / 2); i++) {
			int temp = value1[i];
			value1[i] = value1[(sizef - 1) - i];
			value1[(sizef - 1) - i] = temp;
		}
	}
	void print() {
		/*if (decimal > 0) {
			for (int i = sizef; i > decimal; i--) {
				cout << value1[i];
			}
			cout << '.';
			for (int j = decimal; j > 0; j--) {
				cout << value1[j];
			}
		}
		if (decimal == 0) {*/
		for (int i = 0; i < sizef; i++)
			cout << value1[i];
		cout << endl;
		}
	numbers& operator= (const numbers &other) {
		if (this == &other)
			return *this;
		this->sizef = other.sizef;
		this->si_num = other.si_num;
		delete this->value1;
		this->value1 = new int[other.sizef];
		for (int i = 0; i < other.sizef; i++)
			this->value1[i] = other.value1[i];
		return *this;
		}
	bool operator > (const numbers &other) {
		if (this->si_num == 1 && other.si_num == 0)
			return true;
		if (this->si_num == 0 && other.si_num == 1)
			return false;
		if (this == &other)
			return false;
		if (this->sizef > other.sizef)
			return true;
		if (this->sizef < other.sizef)
			return false;
		if (this->sizef == other.sizef)
			for (int i = 0; i < this->sizef; i++) {
				if (this->value1[i] > other.value1[i])
					return true;
				if (this->value1[i] < other.value1[i])
					return false;
			}
		return false;
		}
	bool operator < (const numbers &other) {
		if (this->si_num == 1 && other.si_num == 0)
			return false;
		if (this->si_num == 0 && other.si_num == 1)
			return true;
		if (this == &other)
			return false;
		if (this->sizef < other.sizef)
			return true;
		if (this->sizef > other.sizef)
			return false;
		if (this->sizef == other.sizef)
			for (int i = 0; i < this->sizef; i++) {
				if (this->value1[i] < other.value1[i])
					return true;
				if (this->value1[i] > other.value1[i])
					return false;
			}
		return false;
	}
	bool operator >= (const numbers &other) {
		if (*this < other)
			return false;
		return true;
	}
	bool operator <= (const numbers &other) {
		if (*this > other)
			return false;
		return true;
	}
	numbers operator+ (const numbers &other) {

		if (this->decimal > other.decimal) {
			int * g = new int[other.sizef + (this->decimal - other.decimal)];
			for (int i = 0; i < other.sizef; i++) 
				g[i] = other.value1[i];
			for (int j = 0; j < this->decimal - other.decimal; j++) 
				g[j+other.sizef] = { 0 };

			numbers r(g, other.sizef + (this->decimal - other.decimal));
			r.decimal = this->decimal;
			return *this + r;
		}
		if (this->decimal < other.decimal) {    
			int * g = new int[this->sizef + (other.decimal - this->decimal)];
			for (int i = 0; i < this->sizef; i++)
				g[i] = this->value1[i];
			for (int j = 0; j < other.decimal - this->decimal; j++)
				g[j+this->sizef] = { 0 };

			cout << endl;
			numbers q(g, this->sizef + (other.decimal - this->decimal));
			q.decimal = other.decimal;
			return q + other;
		}
		if (this->si_num == 0 && other.si_num == 0) {
			cout << "-";
			numbers  tmp1, tmp2;
			tmp2 = *this;
			tmp1 = other;
			tmp2.si_num = 1;
			tmp1.si_num = 1;
			return tmp1 + tmp2;
		}
		if (this->si_num == 0 && other.si_num == 1) {   // still doesn't work 4 no good f ( the F word ) freaking reason if this > other
			if (*this > other) {
				numbers  tmp1, tmp2;
				tmp2 = *this;
				tmp1 = other;
				tmp2.si_num = 1;
				tmp1.si_num = 1;
				cout << "-";
				return tmp2 - tmp1;
			}
			if (*this <= other) {
				numbers  tmp1, tmp2;
				tmp2 = *this;
				tmp1 = other;
				tmp2.si_num = 1;
				tmp1.si_num = 1;
				return tmp1 - tmp2;
			}
		}
			
		if (this->si_num == 1 && other.si_num == 0)
		{                                           // still doesn't work 4 no good f ( the F word ) freaking reason if the second number is bigger
			numbers  tmp1, tmp2;
			tmp2 = *this;
			tmp1 = other;
			tmp2.si_num = 1;
			tmp1.si_num = 1;
			return tmp2 - tmp1;
		}
		int e = this->sizef-1;
		int r = other.sizef-1;
		int p;
		int k = 0;
		int x[100000];
		x[0] = 0;
		while (e>=0 && r>=0) {
			p = this->value1[e] + other.value1[r] + x[k];
			x[k] = p % 10;
			x [++k]= p / 10;
			e--;
			r--;
		}
		if (r >= 0) {
			p = other.value1[r] + x[k];
			x[k] = p % 10;
			x[++k] = p / 10;
			r--;
		}
		if (e >= 0) {
			p = this->value1[e] + x[k];
			x[k] = p % 10;
			x[++k] = p / 10;
			e--;
		}
		while (e >= 0) 
			x[++k] = this->value1[e--];
		while (r >= 0) 
			x[++k] = other.value1[r--];
		k++;
		if (this->decimal > 0 || other.decimal > 0) {
			/*int * u = new int[k + 1];
			for (int i = k; i >= 0; i--)
				u[i] = x[i];
			for (int j = k; j >= k - 1 - decimal; j--) {
				if (j == k - 1 - decimal) {
					u[j] = char('.');
				}
				u[j + 1] = u[j];
			}
			numbers ans0(u, k + 1);
			ans0.reverse();
			return ans0;*/
			numbers ans1(x, k);
			ans1.reverse();
			cout << "10 in power of -" << decimal << " * ";
			return ans1;
		}
		numbers ans1(x, k);
		ans1.reverse();
		return ans1;
	}
	numbers operator- (const numbers & other) {
		if (this->decimal > other.decimal) {
			int * g = new int[other.sizef + (this->decimal - other.decimal)];
			for (int i = 0; i < other.sizef; i++)
				g[i] = other.value1[i];
			for (int j = 0; j < this->decimal - other.decimal; j++)
				g[j + other.sizef] = { 0 };

			numbers r(g, other.sizef + (this->decimal - other.decimal));
			r.decimal = this->decimal;
			return *this - r;
		}
		if (this->decimal < other.decimal) {
			int * g = new int[this->sizef + (other.decimal - this->decimal)];
			for (int i = 0; i < this->sizef; i++)
				g[i] = this->value1[i];
			for (int j = 0; j < other.decimal - this->decimal; j++)
				g[j + this->sizef] = { 0 };

			numbers q(g, this->sizef + (other.decimal - this->decimal));
			q.decimal = other.decimal;
			return q - other;
		}

		if (this->si_num == 0 && other.si_num == 0) {
			if (*this <= other) {
				numbers  tmp1, tmp2;
				tmp2 = *this;
				tmp1 = other;
				tmp1.si_num = 1;
				tmp2.si_num = 1;
				return tmp1 - tmp2;
			}
			if (*this > other) {
				numbers  tmp1, tmp2;
				tmp2 = *this;
				tmp1 = other;
				tmp1.si_num = 1;
				tmp2.si_num = 1;
				cout << "-";
				return tmp2 - tmp1;
			}
		}
		if (this->si_num == 1 && other.si_num == 0) {
			numbers  tmp1, tmp2;
			tmp2 = *this;
			tmp1 = other;
			tmp1.si_num = 1;
			tmp2.si_num = 1;
			return tmp2 + tmp1;
		}
		if (this->si_num == 0 && other.si_num == 1) {
			numbers  tmp1, tmp2;
			tmp2 = *this;
			tmp1 = other;
			tmp1.si_num = 1;
			tmp2.si_num = 1;
			cout << "-";
			return tmp2 + tmp1;
		}
		if (*this < other) {
			numbers  temp1, temp2;
			temp2 = *this;
			temp1 = other;
			cout << "-"<<" ";
			return temp1 - temp2;
		}
		int A = this->sizef-1;
		int t = other.sizef-1;
		int o, p = 0,k = 0;
		int v[100000];
		v[0] = 0;
		while (A >= 0 && t >= 0) {
			o = (this->value1[A]) - (other.value1[t]) + v[k];
			if (o < 0) {
				o += 10;
				v[k++] = o;
				v[k] = -1;
			}
			else {
				v[k++] = o;
				v[k] = 0;
			}
			A--;
			t--;
		}
		while(A>=0){
			o = this->value1[A] + v[k];
			if (o < 0) {
				o += 10;
				v[k++] = o;
				v[k] = -1;
			}
			else {
				v[k++] = o;
				v[k] = 0;
			}
			A--;
	}
		while (t >= 0) {
			o = other.value1[t] + v[k];
			if (o < 0) {
				o += 10;
				v[k++] = o;
				v[k] = -1;
			}
			else {
				v[k++] = o;
				v[k] = 0;
			}
			t--;
		}
		k++;
		if (this->decimal > 0 || other.decimal > 0) {
			numbers ans2(v, k);
			ans2.reverse();
			cout << "10 in power of -" << decimal << " * ";
			return ans2;
		}
		numbers ans2(v, k);
		ans2.reverse();
		return ans2;
}
	numbers operator* (const numbers & other) {
		if (this->decimal > other.decimal) {
			int * g = new int[other.sizef + (this->decimal - other.decimal)];
			for (int i = 0; i < other.sizef; i++)
				g[i] = other.value1[i];
			for (int j = 0; j < this->decimal - other.decimal; j++)
				g[j + other.sizef] = { 0 };

			numbers r(g, other.sizef + (this->decimal - other.decimal));
			r.decimal = this->decimal;
			return *this * r;
		}
		if (this->decimal < other.decimal) {
			int * g = new int[this->sizef + (other.decimal - this->decimal)];
			for (int i = 0; i < this->sizef; i++)
				g[i] = this->value1[i];
			for (int j = 0; j < other.decimal - this->decimal; j++)
				g[j + this->sizef] = { 0 };

			numbers q(g, this->sizef + (other.decimal - this->decimal));
			q.decimal = other.decimal;
			return q * other;
		}

		if (this->si_num == 0 && other.si_num == 1|| this->si_num == 1 && other.si_num == 0) {
			numbers  tmp1, tmp2;
			tmp2 = *this;
			tmp1 = other;
			tmp1.si_num = 1;
			tmp2.si_num = 1;
			cout << "-";
			return tmp2 * tmp1;
		}
		if (this->si_num == 0 && other.si_num == 0) {
			numbers  tmp1, tmp2;
			tmp2 = *this;
			tmp1 = other;
			tmp1.si_num = 1;
			tmp2.si_num = 1;
			return tmp2 * tmp1;
		}
		int l = 0,m = 0,c;
		int * g = new int[this->sizef + 1];
		g[0] = 0;
		for (int j = 0; j < this->sizef; j++)
			g[j+1] = this->value1[j];
		numbers j(g, this->sizef + 1);

		int * value3 = new int [other.sizef + j.sizef];
		for (int i = 0; i < other.sizef + j.sizef; i++)
			value3[i] = 0;

		for (int i = other.sizef - 1; i >= 0; i--) {
			for (int p = j.sizef - 1; p >= 0; p--) {
				m = (j.value1[p]) * (other.value1[i]) + (value3[j.sizef - i + other.sizef - p - 2]) + l;
				c = m % 10;
				l = m / 10;
				value3[j.sizef - i + other.sizef - p - 2] = c;
			}
		}
		if (this->decimal > 0 || other.decimal > 0) {
			numbers q(value3, other.sizef + j.sizef);
			q.reverse();
			cout << "10 in power of -" << this->decimal + other.decimal << " * ";
			return q;
		}
		numbers q(value3, other.sizef + j.sizef);
		q.reverse();
		return q;
	}
	/*numbers operator ^ (const numbers &other) {
		int i = 0;
		numbers var;
		int min_rep1[1] = { 1 };
		numbers minrep1(min_rep1, 1);
		int min_rep[1] = { 2 };
		numbers minrep(min_rep, 1);
		while (this->value1 > 0) {
			var = (numbers(this->value1, this->sizef)*(numbers(this->value1, this->sizef) - minrep1 ))* var;
			*this = *this - minrep;
		}
		return var;
	}*/
};
int main() {
	char *x,*y;
	x = new char[1000000];
	y = new char[1000000];
	cout << "enter your first number: ";
	cin >> x;
	cout << "enter your second number: ";
	cin >> y;
	numbers a(x);
	numbers b(y);
	numbers c = a * b;
	c.print();
	return 0;
}