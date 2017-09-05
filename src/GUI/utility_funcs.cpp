//template <class T> const T& min(const T& a, const T& b) {
//	return !(b<a) ? a : b;     // or: return !comp(b,a)?a:b; for version (2)
//}
#include <qstring.h>
#include <qdatetime.h>
#include <utility_funcs.h>
#include <qstringlist.h>

double min(double x, double y)
{
	if (x > y) return y; else return x;
}
float min(float x, float y)
{
	if (x > y) return y; else return x;

}
int min(int x, int y)
{
	if (x > y) return y; else return x;
}

double max(double x, double y)
{
	return -min(-x, -y);
}
float max(float x, float y)
{
	return -min(-x, -y);

}
int max(int x, int y)
{
	return -min(-x, -y);
}

QString float2date(const double d, QString format, bool ignorefirst50years)
{
	if (ignorefirst50years && d < 18264)
		return QString::number(d);

	qint64 julian = xldate2julian(d);
	QDate date = QDate::fromJulianDay(julian);

	//			QDateTime r = QDateTime::fromTime_t(getValue(propName).todouble() * 86400 - 2209161600, QTimeZone(0));
	//			return r.toString("MMM dd yyyy HH:mm");// QDateTime(getValue(propName));
	return date.toString(format); // "MMM dd yyyy");// QDateTime(getValue(propName));
}
qint64 xldate2julian(const qint64 xldate)
{
	qint64 julian = xldate + 2415020;
	if (xldate >= 60)
		julian--;
	
	return julian;
}

qint64 julian2xldate(const qint64 juliandate)
{
	qint64 date = juliandate - 2415020;// QDate(1900, 1, 1).toJulianDay();
	if (date >= 60)
		date++;
	return date;
}

int dayOfYear(const qint64 xldate)
{
	qint64 julian = xldate2julian(xldate);
	QDate date = QDate::fromJulianDay(julian);
	return date.dayOfYear();
}
double dayOfYear(const double xldate)
{
	double fraction = fmod(xldate, 1.0);
	qint64 xldateint = xldate;
	qint64 julian = xldate2julian(xldateint);
	QDate date = QDate::fromJulianDay(julian);
	double dayofyear = date.dayOfYear() + fraction;
	return dayofyear;

}
/*
std::string GetSystemFolderPaths(int csidl)
{
	wchar_t Folder[1024];
	HRESULT hr = SHGetFolderPathW(0, CSIDL_MYDOCUMENTS, 0, 0, Folder);
	if (SUCCEEDED(hr))
	{
		char str[1024];
		wcstombs(str, Folder, 1023);
		return str;
	}
	else return "";
}
*/
double xldate2julian(const double xldate)
{
	double julian = xldate + 2415020;
	if (xldate >= 60)
		julian--;

	return julian;
}

double julian2xldate(const double juliandate)
{
	double date = juliandate - 2415020;// QDate(1900, 1, 1).toJulianDay();
	if (date >= 60)
		date++;
	return date;
}

double timetodayfraction(int hh, int mm, int ss)
{
	double fraction;
	fraction = ss / 60.0;
	fraction = (fraction + mm) / 60.0;
	fraction = (fraction + hh) / 24.0;
	return fraction;
}

QList<int> dayfractiontotime(double dayFraction)
{
	QTime qtime;
	dayFraction = fmod(dayFraction, 1.0);
	int hh = dayFraction * 24;
	dayFraction = dayFraction * 24.0 - hh;
	int mm = dayFraction * 60;
	dayFraction = dayFraction * 60.0 - mm;
	int ss = dayFraction* 60.0;

	return QList<int>() << hh << mm << ss;
}

QString float2datetime(const double d, QString format, bool ignorefirst50years)
{
	if (ignorefirst50years && d < 18264)
		return QString::number(d);

	double julian = xldate2julian(d);
	QDate date = QDate::fromJulianDay(julian);
	QList<int> timeList = dayfractiontotime(d);
	QTime time = QTime(timeList[0], timeList[1], timeList[2]);
	QDateTime dateTime = QDateTime(date, time);
	//			QDateTime r = QDateTime::fromTime_t(getValue(propName).todouble() * 86400 - 2209161600, QTimeZone(0));
	//			return r.toString("MMM dd yyyy HH:mm");// QDateTime(getValue(propName));
	return dateTime.toString(format); // "MMM dd yyyy");// QDateTime(getValue(propName));
}
QStringList specialSplit(QString s)
{
	QStringList r;
	if (s.indexOf("\"") == -1)
		r = s.split(" ");
	else
	{
		QString leftofq = s.section("\"", 0, 0);
		QString between = s.section("\"", 1, 1);
		QString rightofq = s.section("\"", 2, -1);

		r.append(specialSplit(leftofq));
		r.append(between);
		r.append(specialSplit(rightofq));
	}
	r.removeAll("");
	return r;
}

QStringList extract_by_space_quote(QString s)
{
	QString del1 = "'";
	
	bool inside_quote = false; 
	for (int i = 0; i < s.size(); i++)
	{
		if (s.mid(i, 1) == "'")
		{
			inside_quote = !inside_quote;
			s.remove(i, 1);
		}
		if (inside_quote)
			if (s.mid(i, 1) == " ") s.replace(i,1, "|");

	}
	QStringList out = s.split(" ");
	for (int i = 0; i < out.size(); i++) out[i].replace("|", " ");
	return out; 
}



QString extract_in_between(const QString &s,QString s1, QString s2)
{
	QString out;
	if (!s.contains(s1) && !s.contains(s2)) return out;
	int start = s.indexOf(s1,0);
	int end = s.indexOf(s2, 0);
	if (start == -1) return out; 
	out = s.mid(start+1, end - start-1);
	return out;
}

vector<int> find_indexes_of(const QString &s, QString &s1)
{
	vector<int> out;
	int i = 0;
	while (s.indexOf(s1, i) != -1)
	{
		out.push_back(s.indexOf(s1, i));
		i++; 
	}

	return out; 

}