namespace SFT
{
    internal static class TestDict
    {
        internal static string[] Tokens()
        {
            var res = System.IO.File.ReadAllLines("test.txt");
            return res;
        }
    }
}