using System;

namespace SFT
{
    public static class Program
    {
        private static void TestTree(string str)
        {
            const string spacing = "-------------------------------------------------";
            var t = new SuffixTree(str);
            t.PrintTree();
            Console.WriteLine(t.Contains(str.Substring(0, 3)));
            // ReSharper disable once RedundantAssignment
            t = null;
            Console.WriteLine(spacing);
        }

        private static void Main()
        {
            string[] strings = {"aaaabbbc", "test", "testing_the_suffix_tree"};

            foreach (var s in strings) 
                TestTree(s);
        }
    }
}
