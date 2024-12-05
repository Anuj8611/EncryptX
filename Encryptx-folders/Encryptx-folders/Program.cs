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
            Console.WriteLine("Enter Path of folders");
            string folders = Console.ReadLine();
            if(Directory.Exists(folders))
            {
                Console.WriteLine("Folder exists");
            }
            Console.ReadLine();
        }
    }
}
