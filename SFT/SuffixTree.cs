using System;
using System.Collections.Generic;

namespace SFT
{
    public class SuffixTree
    {
        private class Node
        {
            internal int Start;
            internal int End;
            internal readonly Dictionary<char, Node> Children = new Dictionary<char, Node>();
            public Node SuffixLink;
            internal Node Parent;

            internal Node(int start = 0, int end = 0)
            {
                Start = start;
                End = end;
            }

            internal void AddChild(char c, Node n)
            {
                Children.Add(c, n);
                n.Parent = this;
            }

            internal int Length()
            {
                return End - Start;
            }

            internal bool IsLeaf()
            {
                return Children.Count == 0;
            }
        }

        private readonly string _baseString;
        private readonly Node _root;
        private Node _needsSuffixLink;
        private Node _lastUsedNode;
        private Node _lastUsedLeaf;

        private void RegisterNode(Node n)
        {
            if (_needsSuffixLink != null)
            {
                _needsSuffixLink.SuffixLink = n.Parent;
                _needsSuffixLink = null;
            }
            _lastUsedLeaf = n;
            _lastUsedNode = n.Parent;
        }

        private string NodeText(Node n)
        {
            return _baseString.Substring(n.Start, n.End - n.Start);
        }

        private char Index(Node n)
        {
            return _baseString[n.Start];
        }

        private void PrintNode(Node n, int indent)
        {
            if (n.Children.Count == 0) return;
            foreach (Node child in n.Children.Values)
            {
                for (int i = 0; i < indent; i++) Console.Write("|");
                Console.WriteLine(NodeText(child));
                PrintNode(child, indent + 1);
            }
        }

        public SuffixTree(string baseString)
        {
            if (string.IsNullOrEmpty(baseString))
                throw new ArgumentException($"{nameof(baseString)} must be not empty!");
            
            _root = new Node();
            _baseString = baseString + "$";
            var fullStringNode = new Node(0, 1);
            _root.AddChild(Index(fullStringNode), fullStringNode);

            for (int phase = 0; phase < _baseString.Length - 2; phase++)
            {
                fullStringNode.End++;
                RegisterNode(fullStringNode);
                for (int extension = 1; extension < phase + 1; extension++)
                {
                    var currentNode = _lastUsedNode.SuffixLink ?? _root;
                    int remainingLength = 1 + phase - extension;
                    if (currentNode != _root) remainingLength = _lastUsedLeaf.Length() - 1;
                    while (remainingLength > 0)
                    {
                        int target = phase - remainingLength + 1;
                        if (currentNode.Children.ContainsKey(_baseString[target]))
                        {
                            remainingLength -= currentNode.Children[_baseString[target]].Length();
                            currentNode = currentNode.Children[_baseString[target]];
                        }
                        else break;
                    }
                    if (remainingLength == 0 && currentNode.IsLeaf())
                    {
                        currentNode.End++;
                        RegisterNode(currentNode);
                    }
                    else if (remainingLength == 0 && !currentNode.Children.ContainsKey(_baseString[phase + 1]))
                    {
                        var leaf = new Node(phase + 1, phase + 2);
                        currentNode.AddChild(Index(leaf), leaf);
                        RegisterNode(leaf);
                    }
                    else if (remainingLength < 0 && _baseString[currentNode.End + remainingLength] != _baseString[phase + 1])
                    {
                        currentNode.Parent.Children.Remove(Index(currentNode));

                        var splitNode = new Node(currentNode.Start, currentNode.End + remainingLength);
                        currentNode.Start = currentNode.End + remainingLength;

                        currentNode.Parent.AddChild(Index(splitNode), splitNode);

                        var leaf = new Node(phase + 1, phase + 2);
                        splitNode.AddChild(Index(leaf), leaf);
                        splitNode.AddChild(Index(currentNode), currentNode);

                        RegisterNode(leaf);
                        _needsSuffixLink = splitNode;
                    }
                    else
                    {
                        break;
                    }
                }
                if (_root.Children.ContainsKey(_baseString[phase + 1])) continue;
                {
                    var leaf = new Node(phase + 1, phase + 2);
                    _root.AddChild(Index(leaf), leaf);
                    RegisterNode(_root);
                }
            }
        }

        public void PrintTree()
        {
            Console.WriteLine($"Tree({_baseString}):");
            PrintNode(_root, 0);
        }

        public bool Contains(string s)
        {
            var n = _root.Children[s[0]];
            for (int i = 0; i < s.Length; )
            {
                var curNodeText = NodeText(n);
                foreach (var c in curNodeText)
                {
                    if (c == s[i])
                    {
                        i++;
                        if (i == s.Length)
                            return true;
                    }
                    else
                        return false;
                }
                n = n.Children[s[i]];
            }

            return false;
        }
    }
}
