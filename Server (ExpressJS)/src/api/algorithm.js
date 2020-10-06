const crypto = require('crypto');
const base36 = require(`./../utility/base36`);

const CODE_LENGTH = 6;

let hash = (str, algorithm="sha512") => crypto.createHash(algorithm).update(str).digest('hex');

let generateCode = (username, password, timestamp) => {
    let code = base36.decode( hash(username.substr(0, 6) + Math.floor(timestamp / 10000)) ), intBuilder = "";

    const TEMP_LENGTH = Math.floor(code.length/2);
    for(let i=0;i<TEMP_LENGTH;i++) {
        intBuilder += code.charCodeAt(TEMP_LENGTH+i);
    }

    return base36.encode(code).substr(0, CODE_LENGTH).toUpperCase();
};

class Code {
    constructor(username, password) {
        this.username   = username;
        this.password   = hash(password, 'sha512');
        this.timestamp  = (new Date()).getTime();
        this.code       = generateCode(this.username, this.password, this.timestamp);
    }
}

module.exports = Code;