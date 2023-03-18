using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BlazorWpfApp.Services
{
    public class ArduinoCommunicationService
    {
        SerialPort port;

        public List<int> checkValues()
        {
            if (port == null)
            {
                port = new SerialPort("COM7", 9600);//Set your board COM
                port.Open();
            }


            if (port != null && port.IsOpen)
            {

                port.Write("1"); //"1" is the signal that triggers a response from the board
                string recieve = port.ReadExisting();
                port.Close();

                int waterLevel = Convert.ToInt32(recieve.Substring(0, recieve.IndexOf("#") - 1)); //"#" is the seperator character that signals the end of the waterLevel part of the string
                int soildHumidity = Convert.ToInt32(recieve.Substring(recieve.IndexOf("#") + 1)); //"#" is the seperator character that signals the end of the waterLevel part of the string


                return new List<int> { waterLevel, soildHumidity };

            }

            else
                throw new Exception("Failed to open port");
        }
    }
}
