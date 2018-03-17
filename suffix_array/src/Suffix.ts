import assert = require('assert');

class Suffix
{
    constructor (private text: string, protected offset: number)
    {        
    }

    length(): number
    {
        return this.text.length - this.offset;
    }

    charAt(index: number): string
    {
        assert(index + this.offset < this.text.length, "charAt out of bounds access");
        return this.text.charAt(index + this.offset);
    }

    compareTo(other: Suffix): number
    {
        let minLength: number = Math.min(this.length(), other.length());
        for (let i = 0; i < minLength; ++i)
        {
            if (this.charAt(i) < other.charAt(i))
                return -1;
            if (this.charAt(i) > other.charAt(i))
                return 1;
        }
        return this.length() - other.length();
    }

    toString(): string
    {
        return this.text.substr(this.offset);
    }

    static main(): void
    {
        const s = "banana";
        let s1 = new Suffix(s, 1);
        let s2 = new Suffix(s, 2);
        console.log(s1.compareTo(s2));
        console.log(s2.toString());
    }
}

Suffix.main();

