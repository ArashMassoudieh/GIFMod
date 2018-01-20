//template <class T> const T& min(const T& a, const T& b) {
//	return !(b<a) ? a : b;     // or: return !comp(b,a)?a:b; for version (2)
//}

#ifdef QT_version
#include <qstring.h>
#include <qdatetime.h>
#include <utility_funcs.h>
#include <qstringlist.h>
#include <qdebug.h>
#endif // QT_version

#include <vector>

using namespace std;

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

#ifdef QT_version
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
#endif // QT_version

vector<double> ExcelSerialDateToDMY(double nSerialDate)
{
    // Excel/Lotus 123 have a bug with 29-02-1900. 1900 is not a
    // leap year, but Excel/Lotus 123 think it is...
    vector<double> out(4);
    if (nSerialDate == 60)
    {
        out[2] = 29;
        out[1] = 2;
        out[0] = 1900;
        out[4] = nSerialDate - int(nSerialDate);

        return out;
    }
    else if (nSerialDate < 60)
    {
        // Because of the 29-02-1900 bug, any serial date
        // under 60 is one off... Compensate.
        nSerialDate++;
    }

    // Modified Julian to DMY calculation with an addition of 2415019
    int l = nSerialDate + 68569 + 2415019;
    int n = int(( 4 * l ) / 146097);
            l = l - int(( 146097 * n + 3 ) / 4);
    int i = int(( 4000 * ( l + 1 ) ) / 1461001);
        l = l - int(( 1461 * i ) / 4) + 31;
    int j = int(( 80 * l ) / 2447);
     out[2] = l - int(( 2447 * j ) / 80);
        l = int(j / 11);
        out[1] = j + 2 - ( 12 * l );
    out[0] = 100 * ( n - 49 ) + i + l;
    out[4] = nSerialDate - int(nSerialDate);
    return out;
}


int DMYToExcelSerialDate(vector<double> DMY)
{
    // Excel/Lotus 123 have a bug with 29-02-1900. 1900 is not a
    // leap year, but Excel/Lotus 123 think it is...
    if (DMY[2] == 29 && DMY[1] == 02 && DMY[0]==1900)
        return 60;

    // DMY to Modified Julian calculatie with an extra substraction of 2415019.
    double nSerialDate =
            int(( 1461 * ( DMY[0] + 4800 + int(( DMY[1] - 14 ) / 12) ) ) / 4) +
            int(( 367 * ( DMY[1] - 2 - 12 * ( ( DMY[1] - 14 ) / 12 ) ) ) / 12) -
            int(( 3 * ( int(( DMY[0] + 4900 + int(( DMY[1] - 14 ) / 12) ) / 100) ) ) / 4) +
            DMY[2] - 2415019 - 32075 + DMY[3];

    if (nSerialDate < 60)
    {
        // Because of the 29-02-1900 bug, any serial date
        // under 60 is one off... Compensate.
        nSerialDate--;
    }

    return nSerialDate;
}


#if QT_version
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
#else
double dayOfYear(const double xldate)
{
	vector<double> res = ExcelSerialDateToDMY(xldate);
	return res[2] + res[3];

}
#endif // QT_version

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

#ifdef QT_version
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

double QDate2Xldate(QDateTime &x)
{
	QDateTime base_time1 = QDateTime::fromString("1-1-1900 00:00", "M-d-yyyy hh:mm");
	double xxx = (x.toMSecsSinceEpoch() - base_time1.toMSecsSinceEpoch())/(1000.00*24.0*60.0*60.0)+2;
	return xxx;
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
#endif // QT_version


