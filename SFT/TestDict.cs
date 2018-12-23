namespace SFT
{
    internal static class TestDict
    {
        internal static string[] Tokens()
        {
            var res = System.IO.File.ReadAllLines("test.txt");
            return res;
        }

        internal static string TokensHard()
        {
            var res = System.IO.File.ReadAllText("test.txt");
            return res;
        }
    }
}