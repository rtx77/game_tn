using System;
using System.Runtime.InteropServices;
using System.Text;

class Application
{
    [DllImport("testdll.dll", CharSet = CharSet.Ansi)]
    public static extern int function(IntPtr str1, IntPtr str2);
    public static void Main()
    {
        byte[] buf_1 = new byte[128];//принимаем от сервера
        byte[] buf_2 = new byte[128];//отправляем на сервер

        var pbuf1 = Marshal.AllocHGlobal(1024);
        var pbuf2 = Marshal.AllocHGlobal(1024);


        Marshal.Copy(buf_1, 0, pbuf1, buf_1.Length);
        Marshal.Copy(buf_2, 0, pbuf2, buf_2.Length);

        Console.WriteLine(buf_1[0]);

        int stat = function(pbuf1, pbuf2);

        var result1 = Marshal.PtrToStringUni(pbuf1);
        var result2 = Marshal.PtrToStringUni(pbuf2);

        var data1 = Encoding.Unicode.GetBytes(result1);
        var data2 = Encoding.Unicode.GetBytes(result2);

        Console.WriteLine(data1[1]);

        Marshal.FreeHGlobal(pbuf1);
        Marshal.FreeHGlobal(pbuf2);


        Console.ReadKey();
    }
}