import assert = require('assert');

import {Suffix} from './Suffix'


export class SuffixArray
{
    suffixes: Array<Suffix> = new Array;

    constructor(text: string)
    {
        for (let i = 0; i < text.length; ++i)
        {
            this.suffixes.push(new Suffix(text, i));
        }
        this.suffixes.sort((s1, s2) => { return s1.compareTo(s2) });
    }

    private static lcp(s1: Suffix, s2: Suffix): number
    {
        let commonLength = Math.min(s1.length(), s2.length());
        for (let i = 0; i < commonLength; ++i)
        {
            if (s1.charAt(i) != s2.charAt(i))
            {
                return i;
            }
        }
        return commonLength;
    }

    private lcp(index: number): number
    {
        assert(index > 0, "Index must be greater than 0");
        assert(index < this.suffixes.length, "Index must be smaller than text length");
        return SuffixArray.lcp(this.suffixes[index], this.suffixes[index-1]);
    }

    longestCommonSubstring(): string
    {
        let substringLength = 0;
        let substringIndex  = -1
        for (let i = 1; i < this.suffixes.length; ++i)
        {
            let currentLcp = this.lcp(i);
            if (currentLcp > substringLength)
            {
                substringLength = currentLcp;
                substringIndex = i;
            }
        }
        if (substringIndex >= 0)
            return this.suffixes[substringIndex].toString().substr(0, substringLength);
        else
            return "";
    }

    static main()
    {
        let strings: Array<string> = ["abracadabra", "aacaagtttacaagc"];
        for (let s of strings)
        {
            let suffixArray = new SuffixArray(s);
            console.log("Longest common substring of " + s + ": " + suffixArray.longestCommonSubstring());
        }
    }
}