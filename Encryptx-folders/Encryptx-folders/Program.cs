using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;


namespace Encryptx_folders
{
    class Program
    {
        static void Main(string[] args)

        {
            Console.WriteLine("Enter Path of folder");
            string folders = Console.ReadLine();
            if(Directory.Exists(folders))
            {
                
                Console.WriteLine("Enter Output path ");
                string output = Console.ReadLine();
                
            }
            else
            {
                Console.WriteLine("Folder does not exists");
                Console.Readkey();
            }

            Console.ReadLine();
        }
    }
}
