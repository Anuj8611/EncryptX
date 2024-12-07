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
            Console.WriteLine("Enter Path of folder: ");

            string folders = Console.ReadLine();
            Console.WriteLine();
            if (Directory.Exists(folders))
            {

                Console.WriteLine("Enter Output path: ");
                string output = Console.ReadLine();
                Console.WriteLine();
                

                string[] files = Directory.GetFiles(folders); // Get all files in the folder
                Console.WriteLine("**FILES PRESENT IN THE FOLDER**");
                Console.WriteLine();

                foreach (string file in files)
                {
                    FileInfo finfo = new FileInfo(file);
                    Console.Write(Path.GetFileName(file)); // Display each file
                    Console.Write("       " + finfo.Length);
                    Console.Write("       " + "BYTES");
                    Console.WriteLine("\n");
                    
                }

                Console.WriteLine();
                Console.WriteLine("Adding files to archive......");
                Console.WriteLine();

            }
            else
            {
                Console.WriteLine("Folder does not exists");
                Console.ReadKey();
            }

            Console.ReadLine();
        }
    }
}
