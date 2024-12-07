using System;
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

                // Print headers
                Console.WriteLine("{0,-40} {1,10} {2,6}", "File Name", "Size", "Unit");
                Console.WriteLine(new string('-', 60));

                foreach (string file in files)
                {
                    FileInfo finfo = new FileInfo(file);
                    string fileName = Path.GetFileName(file);
                    long fileSize = finfo.Length;

                    // Format output for alignment
                    Console.WriteLine("{0,-40} {1,10} {2,6}", fileName, fileSize, "BYTES");
                }

                Console.WriteLine();
                Console.WriteLine("Adding files to archive......");
                Console.WriteLine();
            }
            else
            {
                Console.WriteLine("Folder does not exist");
                Console.ReadKey();
            }

            Console.ReadLine();
        }
    }
}
