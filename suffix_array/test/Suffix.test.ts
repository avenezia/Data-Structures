import {Suffix} from '../src/Suffix'

test('offset greater than string length at construction', () => {
    expect(() => {
        new Suffix("test", 4);
      }).toThrow();
});

test('negative offset at construction', () => {
    expect(() => {
        new Suffix("test", -2);
      }).toThrow();
});

test('length', () => {
    let s = new Suffix("testing", 2);
    expect(s.length()).toBe(5);
});

test('charAt in range', () => {
    let s = new Suffix("testing", 4);
    expect(s.charAt(1)).toBe("n");
});

test('charAt negative index', () => {
    let s = new Suffix("testing", 4);
    expect(() => {
        s.charAt(-1)
    }).toThrow();
});

test('charAt out of bounds', () => {
    let s = new Suffix("testing", 4);
    expect(() => {
        s.charAt(3);
    }).toThrow();
});

test('toString', () => {
    let s = new Suffix("testing suffix", 5);
    expect(s.toString()).toBe("ng suffix");
});

test('compareTo less than other', () => {
    const str = "abracadabra";
    const s1 = new Suffix(str, 0);
    const s2 = new Suffix(str, 1);
    expect(s1.compareTo(s2)).toBeLessThan(0);
});

test('compareTo greater than other', () => {
    const str = "abracadabra";
    const s1 = new Suffix(str, 2);
    const s2 = new Suffix(str, 1);
    expect(s1.compareTo(s2)).toBeGreaterThan(0);
});

test('compareTo equal to other', () => {
    const str = "abracadabra";
    const s1 = new Suffix(str, 2);
    const s2 = new Suffix(str, 2);
    expect(s1.compareTo(s2)).toBe(0);
});