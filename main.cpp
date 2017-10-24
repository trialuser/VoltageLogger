#include <iostream>
#include <nutclient.h>
#include <fstream>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <iomanip>


using namespace nut;
using namespace std;

int quit_signaled;

void SigHandler( int signo )
{
//	if (signo == SIGQUIT)
//	{
		cout << endl << "Stop logging..." << endl;
		quit_signaled = 1;
//	}
}

int main(int argc, char** argv)
{
int current_voltage;
int prev_voltage;
int sec;
std::ofstream vmdelet_out;

  try
  {
    time_t t;
    struct tm *t_m;
    t=time(NULL);
    t_m=localtime(&t);
    char name_file[50];
    sprintf(name_file, "voltage-%i-%i-%i.log", t_m->tm_hour, t_m->tm_min, t_m->tm_sec );

    Client* client = new TcpClient("localhost", 3493);
    Device mydev = client->getDevice("inelt-ups");
    Variable var = mydev.getVariable("input.voltage");

    prev_voltage = stoi(var.getValue()[0]);

    vmdelet_out.open( name_file, std::ios::app);
   	vmdelet_out << var.getValue()[0]<< " " << t_m->tm_hour<< t_m->tm_min<< t_m->tm_sec <<endl;
	vmdelet_out.close();
	cout << "Start voltage is: " << prev_voltage << endl;
	cout << "Write log in: " << name_file << endl;

	signal(SIGINT, SigHandler);

	while ( !quit_signaled )
    {
    	usleep(10000);
    	t=time(NULL);
    	t_m=localtime(&t);

    	current_voltage = stoi(var.getValue()[0]);
    	if ( current_voltage != prev_voltage )
    	{
    		prev_voltage = current_voltage;
    		vmdelet_out.open( name_file, std::ios::app);
    		vmdelet_out << var.getValue()[0]<< " " << t_m->tm_hour<< t_m->tm_min<< setw(2) <<  setfill('0') << t_m->tm_sec <<endl;
    		vmdelet_out.close();
    		cout << var.getValue()[0]<< " " << t_m->tm_hour<<":"<< t_m->tm_min<<":"<< setw(2) <<  setfill('0') << t_m->tm_sec << endl;
    	}
    }

  }
  catch(NutException& ex)
  {
    cerr << "Unexpected problem : " << ex.str() << endl;
  }
  return 0;
}




