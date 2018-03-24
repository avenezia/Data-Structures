import {SuffixArray} from '../src/SuffixArray'

test('longestCommonSubstring of banana', () => {
    let s = new SuffixArray("banana");
    expect(s.longestCommonSubstring()).toBe("ana");
});

test('longestCommonSubstring of abracadabra', () => {
    let s = new SuffixArray("abracadabra");
    expect(s.longestCommonSubstring()).toBe("abra");
});

test('longestCommonSubstring of dna like string', () => {
    let s = new SuffixArray("aacaagttatacaagttac");
    expect(s.longestCommonSubstring()).toBe("acaagtta");
});

test('longestCommonSubstring of empty string', () => {
    let s = new SuffixArray("");
    expect(s.longestCommonSubstring()).toBe("");
})

test('longestCommonSubstring of one character string', () => {
    let s = new SuffixArray("a");
    expect(s.longestCommonSubstring()).toBe("");
})

test('longestCommonSubstring of string with no common characters', () => {
    let s = new SuffixArray("abcdefghijklmnopqrs");
    expect(s.longestCommonSubstring()).toBe("");
})