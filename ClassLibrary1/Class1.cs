using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace ClassLibrary1
{
    public class Class1
    {
        public void Test()
        {
            using (var ws = File.AppendText(@"C:\Users\Monkey\Documents\SimConnectLandingDetector\test.txt"))
            {
                ws.WriteLine(string.Format("{0} test!", DateTime.Now));
            }
        }
    }
}
