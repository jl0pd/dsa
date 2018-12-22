using System;
using System.Diagnostics;

namespace SFT
{
    public static class Program
    {
        private static void Main()
        {
            var strings = TestDict.Tokens();
            foreach (var s in strings)
            {
                string lookupStr = s;
                Console.WriteLine(s);
                TimeIt(s, lookupStr);
                Console.Write($"len: {s.Length}");
                Console.WriteLine();
                Console.WriteLine();
            }
        }

        private static void TimeIt(string s, string l)
        {
            var t = CalcCreate(s);
            
            CalcSearch(t, l);
            // ReSharper disable once RedundantAssignment
            t = null;
        }

        private static SuffixTree CalcCreate(string str)
        {
            var stopwatch = new Stopwatch();
            stopwatch.Start();
            var t = new SuffixTree(str);
            stopwatch.Stop();
            Console.WriteLine($"create: {stopwatch.Elapsed.TotalMilliseconds}ms");
            return t;
        }

        private static bool CalcSearch(SuffixTree t, string s)
        {
            var stopwatch = new Stopwatch();
            stopwatch.Start();
            var r = t.Contains(s);
            stopwatch.Stop();
            Console.WriteLine($"search: {stopwatch.Elapsed.TotalMilliseconds}ms -> {r}");
            return r;
        }
    }
}
