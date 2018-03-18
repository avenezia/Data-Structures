import assert = require('assert');

export class Suffix
{
    constructor (private text: string, protected offset: number)
    {
        assert(offset >= 0, "offset must be positive");
        assert(offset < text.length, "offset must be lessn than string length");
    }

    length(): number
    {
        return this.text.length - this.offset;
    }

    charAt(index: number): string
    {
        assert(index >= 0, "index must be >= 0")
        assert(index + this.offset < this.text.length, "charAt out of bounds access");
        return this.text.charAt(index + this.offset);
    }

    compareTo(other: Suffix): number
    {
        const minLength: number = Math.min(this.length(), other.length());
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
}

