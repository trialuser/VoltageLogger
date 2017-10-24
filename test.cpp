/*
 * test.cpp
 *
 *  Created on: Oct 24, 2017
 *      Author: npp
 *      Печатает все содержимое varibles в stdio
 */


#include <iostream>
#include <nutclient.h>
using namespace nut;
using namespace std;

int main(int argc, char** argv)
{
  try
  {
    Client* client = new TcpClient("localhost", 3493);

    Device mydev = client->getDevice("inelt-ups");

	set<Variable> variables = mydev.getVariables();
	set<Variable>::iterator vit;

	for(vit=variables.begin(); vit != variables.end(); ++vit)
	{
	cout << endl;
		Variable variable = *vit;
		cout << "Parameter name: " << variable.getName().c_str()<< endl;


	   vector<string> values = variable.getValue();
	   vector<string>::iterator valit;
	   for(valit = values.begin(); valit != values.end(); ++valit)
	   {
			string value = *valit;
			cout << "value: " << value.c_str() << endl;
	   }
	}

  }
  catch(NutException& ex)
  {
    cerr << "Unexpected problem : " << ex.str() << endl;
  }
  return 0;
}
