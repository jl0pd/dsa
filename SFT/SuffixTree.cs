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

        private static void PrintSuffixLink(Node n)
        {
            Console.WriteLine($"{n.Start}-{n.End} -> {n.SuffixLink.Start}-{n.SuffixLink.End}");
            if (n.Children.Count == 0) return;
            foreach (var child in n.Children.Values)
                PrintSuffixLink(child);
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
                fullStringNode.End++; //Extension 0: Add character to fullStringNode
                RegisterNode(fullStringNode);
                for (int extension = 1; extension < phase + 1; extension++)
                {
                    if (_lastUsedNode.SuffixLink != null)
                    {
                        Console.WriteLine($"Used SL: {_lastUsedNode.Start}-{_lastUsedNode.End} -> {_lastUsedNode.SuffixLink.Start}-{_lastUsedNode.SuffixLink.End}");
                        if (_lastUsedNode.SuffixLink == _lastUsedNode) Console.WriteLine("SCREAM");
                    }
                    //Use suffix links to determine a better starting point
                    var currentNode = _lastUsedNode.SuffixLink ?? _root;
                    int remainingLength = 1 + phase - extension; //The amount of characters to be compared
                    if (currentNode != _root) remainingLength = _lastUsedLeaf.Length() - 1;
                    Console.WriteLine($"{phase}-{extension}REM: {remainingLength}");
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
                    //Rule 1: We extend the leaf by the new character
                    if (remainingLength == 0 && currentNode.IsLeaf())
                    {
                        currentNode.End++;
                        RegisterNode(currentNode);
                    }
                    //Rule 2: We add a leaf to the node ending exactly at i
                    else if (remainingLength == 0 && !currentNode.Children.ContainsKey(_baseString[phase + 1]))
                    {
                        var leaf = new Node(phase + 1, phase + 2);
                        currentNode.AddChild(Index(leaf), leaf);
                        RegisterNode(leaf);
                    }
                    //Rule 2: We split the node to insert the new character (Only if there is not already a fitting node!)
                    else if (remainingLength < 0 && _baseString[currentNode.End + remainingLength] != _baseString[phase + 1])
                    {
                        Console.WriteLine($"split {NodeText(currentNode)} to insert {_baseString[phase + 1]}");
                        //Free current node from parent
                        currentNode.Parent.Children.Remove(Index(currentNode));

                        //Modify content of nodes
                        var splitNode = new Node(currentNode.Start, currentNode.End + remainingLength);
                        currentNode.Start = currentNode.End + remainingLength;

                        //Add split node to parent
                        currentNode.Parent.AddChild(Index(splitNode), splitNode);

                        //Set children for new node
                        var leaf = new Node(phase + 1, phase + 2);
                        splitNode.AddChild(Index(leaf), leaf);
                        splitNode.AddChild(Index(currentNode), currentNode);

                        RegisterNode(leaf);
                        _needsSuffixLink = splitNode;
                    }
                    else //Rule 3: We do nothing (Only creates an implicit suffix tree)
                    {
                        Console.WriteLine($"NOTHING {extension} / {phase}; REM: {remainingLength}");
                        break; //Rule 3 is a show stopper
                    }
                }
                //Extension (phase + 1): Create new node (Only if necessary!)
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

        public void PrintSuffixLinks()
        {
            PrintSuffixLink(_root);
        }

        public bool Contains(string s)
        {
            var n = _root.Children[s[0]];
            var lookupString = s.Substring(0);
            for (int i = 0; i < lookupString.Length; )
            {
                var curNodeText = NodeText(n);
                foreach (var c in curNodeText)
                {
                    if (c == lookupString[i])
                    {
                        i++;
                        if (i == lookupString.Length) return true;
                    }
                    else
                        return false;
                }
                n = n.Children[lookupString[i]];
            }

            return false;
        }
    }
}
