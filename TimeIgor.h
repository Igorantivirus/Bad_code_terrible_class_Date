#include<iostream>
#include<windows.h>
using namespace std;
const int sp_mes[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const int sp_mes_v[13] = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const int sum_mes[14] = { 0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
const int sum_mes_v[14] = { 0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 };
namespace timeIgor {
	class Time {
	public:
		//konstruktori
		Time() {
			this->sec = 0;
			this->den = 0;
		}
		Time(int sec) {
			this->sec = sec;
			this->den = 0;
			secRound();
		}
		Time(int sec, int den) {
			this->sec = sec;
			this->den = den;
			secRound();
		}
		Time(const char* tim) {
			this->sec = chr(tim);
			this->den = 0;
			secRound();
		}
		//metodi
		void timer(bool ZapuckTimer = 0) {
			if (ZapuckTimer) {
				if (this->sec < 0) {
					this->sec = time(NULL) * -1;
				}
				else {
					this->den = this->den * 86400 + this->sec;
					this->sec = time(NULL) * -1;
				}
			}
			else {
				if (this->sec < 0) {
					this->sec = this->den % 86400;
					this->den = this->den / 86400;
				}
			}
		}
		void timeNow(int pois = 0) {
			this->sec = (time(NULL) % 86400) + (pois * 3600);
		}
		int seconds() {
			return this->sec;
		}
		int days() {
			return this->den;
		}
		int second() {
			return this->sec % 60;
		}
		int minute() {
			return this->sec % 3600 / 60;
		}
		int hour() {
			return this->sec / 3600;
		}
		//operatori
		//bulevie
		//<=
		bool operator<=(int tim) {
			return this->sec <= tim;
		}
		bool operator<=(const char* tim) {
			return this->sec <= chr(tim);
		}
		bool operator<=(Time& tim) {
			return this->sec <= tim.sec;
		}
		//<
		bool operator<(int tim) {
			return this->sec < tim;
		}
		bool operator<(const char* tim) {
			return this->sec < chr(tim);
		}
		bool operator<(Time& tim) {
			return this->sec < tim.sec;
		}
		//>=
		bool operator>=(int tim) {
			return this->sec >= tim;
		}
		bool operator>=(const char* tim) {
			return this->sec >= chr(tim);
		}
		bool operator>=(Time& tim) {
			return this->sec >= tim.sec;
		}
		//>
		bool operator>(int tim) {
			return this->sec > tim;
		}
		bool operator>(const char* tim) {
			return this->sec > chr(tim);
		}
		bool operator>(Time& tim) {
			return this->sec > tim.sec;
		}
		//==
		bool operator==(int tim) {
			return this->sec == tim;
		}
		bool operator==(const char* tim) {
			return this->sec == chr(tim);
		}
		bool operator==(Time& tim) {
			return this->sec == tim.sec;
		}
		//matematicheskie
		//-=
		void operator-=(int tim) {
			this->sec -= tim;
			secRound();
		}
		void operator-=(const char* tim) {
			this->sec -= chr(tim);
			secRound();
		}
		void operator-=(Time& tim) {
			this->sec -= tim.sec;
			this->den -= tim.den;
			secRound();
		}
		//-
		Time& operator-(int tim) {
			Time otv = this->sec - tim;
			return otv;
		}
		Time& operator-(const char* tim) {
			Time otv = this->sec - chr(tim);
			return otv;
		}
		Time& operator-(Time& tim) {
			/*
			ќператор времени принимает другое врем€
			заполн€ет все полн€ одного класса от переменных другого
			потом возвращает этот класс
			далее в моЄм случае всЄ начинает работать с << в строчке 201
			*/
			Time otv = this->sec - tim.sec;
			otv.den = this->den - tim.den;
			return otv;
		}
		//+=
		void operator+=(int tim) {
			this->sec += tim;
			secRound();
		}
		void operator+=(const char* tim) {
			this->sec += chr(tim);
			secRound();
		}
		void operator+=(Time& tim) {
			this->sec += tim.sec;
			this->den += tim.den;
			secRound();
		}
		//+
		Time& operator+(int tim) {
			Time otv = this->sec + tim;
			return otv;
		}
		Time& operator+(const char* tim) {
			Time otv = this->sec + chr(tim);
			return otv;
		}
		Time& operator+(Time& tim) {
			Time otv = this->sec + tim.sec;
			otv.den = this->den + tim.den;
			return otv;
		}
		//=
		Time& operator=(int tim) {
			this->sec = tim;
			this->den = 0;
			secRound();
			return *this;
		}
		Time& operator=(const char* tim) {
			this->sec = chr(tim);
			this->den = 0;
			secRound();
			return *this;
		}
		Time& operator=(Time& tim) {
			this->sec = tim.sec;
			this->den = tim.den;
			return *this;
		}
		//vivod
		friend ostream& operator<<(ostream& out, Time& tim) {
			/*
			принимаем объект класса из оператора - (или другого любого)
			делаем вывод и всЄ!
			“”“ всЄ идеально работает, теперь что происходит в Date (строчка 440)
			*/
			if (tim.sec < 0) {
				int t = tim.sec + time(NULL);
				out << t / 36000 << t / 3600 % 10 << ':' << t % 3600 / 600 << t % 3600 / 60 % 10 << ':' << t % 60 / 10 << t % 60 % 10;
			}
			else {
				out << tim.sec / 36000 << tim.sec / 3600 % 10 << ':' << tim.sec % 3600 / 600 << tim.sec % 3600 / 60 % 10 << ':' << tim.sec % 60 / 10 << tim.sec % 60 % 10;
			}
			return out;
		}
	private:
		int sec;
		int den;
		void toTime(int& s, int& m, int& h) {
			h = s / 3600;
			m = (s % 3600) / 60;
			s %= 60;
		}
		void toChis(const char* dat, int& s, int& m, int& h, int el = 0) {
			s = m = h = 0;
			int sizePr = el;
			while ((dat[sizePr] >= 48) && (dat[sizePr] <= 57)) {
				sizePr++;
			}
			for (int i = el; i < sizePr; i++) {
				h += (dat[i] - 48) * pow(10, sizePr - i - 1);
			}
			m = ((dat[sizePr + 1] - 48) * 10) + (dat[sizePr + 2] - 48);
			s = ((dat[sizePr + 4] - 48) * 10) + (dat[sizePr + 5] - 48);
		}
		int chr(const char* tim) {
			int s, m, h, zn = 1;
			if (tim[0] == '-') { toChis(tim, s, m, h, 1); zn = -1; }
			else { toChis(tim, s, m, h); }
			return (s + m * 60 + h * 3600) * zn;
		}
		void secRound() {
			while (this->sec < 0) { this->sec += 86400; this->den--; }
			this->den += (this->sec / 86400);
			this->sec -= int(this->sec / 86400) * 86400;
		}
	};

	void sleep(int son) {
		int tim = time(NULL) + son;
		while(time(NULL) < tim){}
	}
	void toTime(int& s, int& m, int& h, int& d) {
		while (s < 0) { s += 86400; d--; }
		d = s / 86400;
		s %= 86400;
		h = s / 3600;
		s %= 3600;
		m = s / 60;
		s %= 60;
	}
	void timeSort(int& s, int& m, int& h, int& d) {
		m += s / 60;
		s %= 60;
		h += m / 60;
		m %= 60;
		d += h / 24;
		h %= 24;
	}
	void secondsRound(int& s) {
		while (s < 0) { s += 86400; }
		s %= 86400;
	}
	int timer(bool ZapuckTimer) {
		static int clo = time(NULL);
		if (ZapuckTimer) { clo = time(NULL); }
		else { clo = time(NULL) - clo; }
		return clo;
	}

	class Date {
	public:
		//konstruktori
		Date() {
			this->den = 1;
		}
		Date(int ch) {
			this->den = ch;
		}
		Date(const char* dat) {
			this->den = chr(dat);
		}
		Date(Date& dat) {
			this->den = dat.den;
		}
		//metodi
		bool leap() {
			int d, m, g;
			toDate(d, m, g);
			return (((g % 4 == 0) && (g % 100 != 0)) || (g % 400 == 0));
		}
		void dateCount(int& d, int& m, int& g) {
			d = this->den; m = g = 0;
			g = d / 365.2425;
			d -= g * 365.2425;
			m = 1;
			++g;
			if (((g % 4 == 0) && (g % 100 == 0)) || (g % 400 == 0)) {
				while (d >= sp_mes[m]) {
					d -= sp_mes[m];
					m++;
				}
			}
			else {
				while (d >= sp_mes_v[m]) {
					d -= sp_mes_v[m];
					m++;
				}
			}
			--g;
			--m;
		}
		void dateNow(int pois = 0) {
			this->den = ((time(NULL) + (pois * 3600)) / 86400) + 719178;
		}
		int days() {
			return this->den;
		}
		int day() {
			int d = this->den, m = 0, g = 0;
			toDate(d, m, g);
			return d;
		}
		int month() {
			int d = this->den, m = 0, g = 0;
			toDate(d, m, g);
			return m;
		}
		int year() {
			int d = this->den, m = 0, g = 0;
			toDate(d, m, g);
			return g;
		}
		int weeks() {
			return this->den / 7;
		}
		int dayWeek() {
			return ((this->den - 1) % 7) + 1;
		}
		//operatori
		//bulevie
		//<=
		bool operator<=(int dat) {
			return this->den <= dat;
		}
		bool operator<=(const char* dat) {
			return this->den <= chr(dat);
		}
		bool operator<=(Date& dat) {
			return this->den <= dat.den;
		}
		bool operator<=(Time& tim) {
			return this->den <= tim.days();
		}
		//<
		bool operator<(int dat) {
			return this->den < dat;
		}
		bool operator<(const char* dat) {
			return this->den < chr(dat);
		}
		bool operator<(Date& dat) {
			return this->den < dat.den;
		}
		bool operator<(Time& tim) {
			return this->den < tim.days();
		}
		//>=
		bool operator>=(int dat) {
			return this->den >= dat;
		}
		bool operator>=(const char* dat) {
			return this->den >= chr(dat);
		}
		bool operator>=(Date& dat) {
			return this->den >= dat.den;
		}
		bool operator>=(Time& tim) {
			return this->den >= tim.days();
		}
		//>
		bool operator>(int dat) {
			return this->den > dat;
		}
		bool operator>(const char* dat) {
			return this->den > chr(dat);
		}
		bool operator>(Date& dat) {
			return this->den > dat.den;
		}
		bool operator>(Time& tim) {
			return this->den > tim.days();
		}
		//==
		bool operator==(int dat) {
			return this->den == dat;
		}
		bool operator==(const char* dat) {
			return this->den == chr(dat);
		}
		bool operator==(Date& dat) {
			return this->den == dat.den;
		}
		bool operator==(Time& tim) {
			return this->den == tim.days();
		}
		//matematicheskie
		//-=
		void operator-=(int dat) {
			this->den -= dat;
		}
		void operator-=(const char* dat) {
			this->den -= chr(dat);
		}
		void operator-=(Date& dat) {
			this->den -= dat.den;
		}
		void operator-=(Time& tim) {
			this->den -= tim.days();
		}
		//-
		Date& operator-(int dat) {
			Date otv = this->den - dat;
			return otv;
		}
		Date& operator-(const char* dat) {
			Date otv = this->den - chr(dat);
			return otv;
		}
		Date& operator-(Date& dat) {
			/*
			мы так же принимаем объект класса
			создаЄм класс отве, заполн€ем его пол€
			возвращаем класс ответ
			Ќќ!!!
			если проверить отладкой или промежуточным временным кодом, то тут всЄ »ƒ≈јЋ№Ќќ!!!
			все данные класса правильные и всЄ круто!
			но далее этот объект по коду из main идЄт в << (строчка 504)
			*/
			Date otv = this->den - dat.den;
			return otv;
		}
		Date& operator-(Time& tim) {
			Date otv = this->den - tim.days();
			return otv;
		}
		//+=
		void operator+=(int dat) {
			this->den += dat;
		}
		void operator+=(const char* dat) {
			this->den += chr(dat);
		}
		void operator+=(Date& dat) {
			this->den += dat.den;
		}
		void operator+=(Time& tim) {
			this->den += tim.days();
		}
		//+
		Date& operator+(int dat) {
			Date otv = this->den + dat;
			return otv;
		}
		Date& operator+(const char* dat) {
			Date otv = this->den + chr(dat);
			return otv;
		}
		Date& operator+(Date& dat) {
			Date otv = this->den + dat.den;
			return otv;
		}
		Date& operator+(Time& tim) {
			Date otv = this->den + tim.days();
			return otv;
		}
		//=
		Date& operator=(int dat) {
			this->den = dat;
			return *this;
		}
		Date& operator=(const char* dat) {
			this->den = chr(dat);
			return *this;
		}
		Date& operator=(Date& dat) {
			this->den = dat.den;
			return *this;
		}
		Date& operator=(Time& tim) {
			this->den = tim.days();
		}
		//vivod
		friend ostream& operator<<(ostream& out, Date& dat) {
			/*
			а здесь ужЄ всЄ! ќн принимает так же объект класса как в Time
			но dat.days() или dat.den (в данно мслучае взаимо замен€емые) вывод€т вместо данных класса otv из оператора -
			какуюто ерунду
			то есть во врем€ передачи объекта класса otv из operator- в operator<< 
			данные тер€ютс€!!!
			и всЄ! :(
			*/
			int d = dat.days(), m = 0, g = 0, zn = 1;
			if (d <= 0) { out << '-'; d = (d * -1) + 1; }
			dat.toDate(d, m, g);
			out << d / 10 << d % 10 << ':' << m / 10 << m % 10 << ':' << g;
			return out;
		}
	private:
		int den;
		void toDate(int& d, int& m, int& g) {
			g = int((d + 365.25) / 365.2425);
			d -= int(g * 365.2425 - 365.25);
			m = 1;
			if (((g % 4 == 0) && (g % 100 != 0)) || (g % 400 == 0)) {
				while (sum_mes_v[m] < d) { m++; }
				d -= sum_mes_v[m - 1];
				--m;
			}
			else {
				while (sum_mes[m] < d) { m++; }
				d -= sum_mes[m - 1];
				--m;
			}
		}
		int toDen(int d, int m, int g) {//дата переводитс€ в кол-во дней, прошедших с 01.01.1 по выведенной формуле: (d + (дни в мес€це) + g * 365 + (g - 1) / 4 - g / 100 + g / 400 - 365)
			return d + ((((g % 4 == 0) && (g % 100 != 0)) || (g % 400 == 0)) ? (sum_mes_v[m]) : (sum_mes[m])) + g * 365.2425 - 365.25 + ((g == 1) ? (1) : (0));
		}
		void toChis(const char* dat, int& d, int& m, int& g, int el = 0) {//разпаковывает чаровский массив даты в день, мес€ц, год
			d = m = g = 0;
			d = ((dat[el] - 48) * 10) + (dat[el + 1] - 48);
			m = ((dat[el + 3] - 48) * 10) + (dat[el + 4] - 48);
			int size = 0;
			while (dat[size] != '\0') { size++; }
			int count = 0;
			for (int i = (size - 1); i > el + 5; i--) {
				g += (dat[i] - 48) * pow(10, count);
				count++;
			}
		}
		int chr(const char* dat) {
			int d = 0, m = 0, g = 0, zn = 1;
			if (dat[0] == '-') { zn = -1; toChis(dat, d, m, g, 1); }
			else { toChis(dat, d, m, g); }
			cout << "vnutr cod " << d << ":" << m << ":" << g << endl;
			d = toDen(d, m, g);
			cout << "vnutr cod " << d << endl;
			if (zn == -1) { d--; }
			return (d * zn);
		}
	};

	bool leap(int g) {
		return (((g % 4 == 0) && (g % 100 != 0)) || (g % 400 == 0));
	}
	void toDate(int& d, int& m, int& g) {
		g = int((d + 365.25) / 365.2425);
		d -= int(g * 365.2425 - 365.25);
		m = 1;
		if (((g % 4 == 0) && (g % 100 != 0)) || (g % 400 == 0)) {
			while (sum_mes_v[m] < d) { m++; }
			d -= sum_mes_v[m - 1];
			--m;
		}
		else {
			while (sum_mes[m] < d) { m++; }
			d -= sum_mes[m - 1];
			--m;
		}
	}
}