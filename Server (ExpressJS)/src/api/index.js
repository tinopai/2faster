const router = require('express').Router();
const Code = require('./algorithm.js');
const config = require('./../../config.json');

const Joi = require('joi');
const userSchema = Joi.object({
    username:   Joi.string().alphanum().required().min(1),
    password:   Joi.string().alphanum().required().min(1),
    twofactor:  Joi.string().alphanum().required().length(config.twofa.code.length)
});

router.post("/login", async(req, res) => {
    console.log(req.body, req.params, req.query, req.headers);
    const validation = await userSchema.validate(req.body);
    
    if(validation.error) return res.status(400).json({
        success: false,
        message: validation.error.message
    });

    const code = new Code(validation.value.username, validation.value.password);
    if(code.code == validation.value.twofactor.toUpperCase()) return res.status(200).json({
        success: false,
        message: "Invalid 2FA code"
    });

    return res.status(200).json({
        success: true
    });
});

module.exports = router;