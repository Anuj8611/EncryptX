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
                Console.WriteLine("Enter Output path: ");
                string output = Console.ReadLine();
                Console.WriteLine();
                Console.WriteLine("Adding files to resource archive......");
                Console.WriteLine();

                try
                {
                    using (var stream = new FileStream(output + "\\output.res", FileMode.Create, FileAccess.Write))
                    using (BinaryWriter bw = new BinaryWriter(stream))
                    {
                        // Write "RESX" as the first 4 bytes
                        bw.Write(new byte[] { (byte)'R', (byte)'E', (byte)'S', (byte)'X' });
                        Int32 ab = 0;
                        bw.Write(ab);

                        foreach (string file in files)
                        {
                            FileInfo finfo = new FileInfo(file);
                            string fileName = Path.GetFileName(file);
                            byte[] fileNameBytes = System.Text.Encoding.UTF8.GetBytes(fileName); // Encode filename
                            long fileSize = finfo.Length;

                            // Write filename length (4 bytes)
                            //bw.Write((Int32)fileNameBytes.Length);

                            // Write filename as raw bytes
                            bw.Write(fileNameBytes);

                            // Write file size (4 bytes)
                            bw.Write((Int32)fileSize);
                        }
                    }

                    Console.WriteLine("Resource archive created successfully.");
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.Message);
                }
            }
            else
            {
                Console.WriteLine("Folder does not exist");
            }

            Console.ReadLine();
        }
    }
}
