using System;
using System.Diagnostics;

namespace SFT
{
    public static class Program
    {
        private static void Main()
        {
            var mainStr = TestDict.TokensHard();

            var t = new SuffixTree(mainStr);
            for (var i = 1; i < 500; i++)
            {
                var start = 0;
                var str = mainStr.Substring(start, i);
                
                double elapsed = 0;
                for (var j = 0; j < 1000; j++)
                    elapsed += CalcSearch(t, str);
                elapsed /= 1000;
                Console.WriteLine($"{i}\t{elapsed}");
            }
        }

        private static double CalcSearch(SuffixTree t, string s)
        {
            var stopwatch = new Stopwatch();
            stopwatch.Start();
            var r = t.Contains(s);
            stopwatch.Stop();
            return stopwatch.Elapsed.TotalMilliseconds;
        }
    }
}
