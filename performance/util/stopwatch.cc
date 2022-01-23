//#include "stopwatch.h"
//#if defined _WIN32
//#include <Windows.h>
//__declspec(dllimport) void __stdcall sleep(unsigned long dwMilliseconds);
//#else
//#include <unistd.h>
//#endif
//
//
//int test_stopwatch03(int test_no, unsigned long)
//{
//	bool rc = true;
//	switch (test_no)
//	{
//	default:
//		return -1;
//	case 0:
//		return 4;
//	case 1:
//	{
//		TimerBaseGetTimeOfDay tb;
//		tb.Start();
//		sleep(5);
//		unsigned dt1 = tb.GetMs();
//		sleep(20);
//		unsigned dt2 = tb.GetMs();
//		sleep(35);
//		unsigned dt3 = tb.GetMs();
//	}
//		{
//			TimerBaseClock tb;
//			tb.Start();
//			sleep(5);
//			unsigned dt1 = tb.GetMs();
//			sleep(20);
//			unsigned dt2 = tb.GetMs();
//			sleep(35);
//			unsigned dt3 = tb.GetMs();
//		}
//		break;
//
//	case 2:
//	{
//		unsigned dt1, dt2, dt3;
//		Stopwatch sw;
//		sleep(15);
//		dt1 = sw.Show();
//		rc &= (dt1 == sw.LapGet());
//		rc &= (15 <= dt1 && dt1 <= 32);
//		sleep(25);
//		dt2 = sw.Show();
//		rc &= (dt2 == sw.LapGet());
//		rc &= (dt1 + 25 <= dt2 && dt2 <= dt1 + 32);
//		sleep(15);
//		dt3 = sw.Stop();
//		rc &= (dt3 == sw.LapGet());
//		rc &= (dt2 + 15 <= dt3 && dt3 <= dt2 + 32);
//		break;
//	}
//
//	case 3:
//	{
//		unsigned dt1, dt2, dt3, dt4;
//		Stopwatch sw("timing run", false);
//		sleep(10);
//		dt1 = sw.Start();
//		rc &= (dt1 == 0);
//		sleep(15);
//		dt2 = sw.Start("event1");
//		rc &= (15 <= dt2 && dt2 <= 32);
//		sleep(25);
//		dt3 = sw.Start("event2");
//		rc &= (25 <= dt3 && dt3 <= 32);
//		sleep(5);
//		dt4 = sw.Stop("event3");
//		rc &= (5 <= dt4 && dt4 <= 32);
//		break;
//	}
//
//	case 4:
//	{
//		unsigned dt1, dt2;
//		Stopwatch sw("");
//		sleep(15);
//		dt1 = sw.Show("");
//		rc &= (15 <= dt1 && dt1 <= 32);
//		dt2 = sw.Start("");
//		rc &= (15 <= dt2 && dt2 <= 32);
//		break;
//	}
//	} //	end switch
//	return rc ? 1 : 0;
//}