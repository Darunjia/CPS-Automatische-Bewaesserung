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

        public List<int> ReadSensors()
        {
            if (port == null)
            {
                port = new SerialPort("COM4", 9600);//Set your board COM
                try
                {
                    port.Open();
                }
                catch (Exception)
                {


                }
                if (!port.IsOpen)
                {
                    port = new SerialPort("COM5", 9600);//Set your board COM
                }
            }


            if (port != null && port.IsOpen)
            {

                port.Write("1"); //"1" is the signal that triggers a response from the board
                string recieve = port.ReadExisting();
                int waterLevel = 0;
                int soilHumidity = 0;
                try
                {
                    if (!String.IsNullOrEmpty(recieve) && recieve.Contains('#'))
                    {
                        waterLevel = Convert.ToInt32(recieve.Substring(0, recieve.IndexOf("#"))); //"#" is the seperator character that signals the end of the waterLevel part of the string
                        waterLevel = (int)((waterLevel / 30.0) * 100); //Convert to percentage
                        soilHumidity = Convert.ToInt32(recieve.Substring(recieve.IndexOf("#") + 1)); //"#" is the seperator character that signals the end of the waterLevel part of the string
                        soilHumidity = (int)((soilHumidity / 1000.0) * 100);
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex);
                }
                return new List<int> { waterLevel, soilHumidity };

            }

            else
                throw new Exception("Failed to open port");
            // return new List<int> { 0, 0 };
        }

        public List<int> ReadSensorsMock()
        {
            return new List<int> { 25, 50 };
        }
    }
}
