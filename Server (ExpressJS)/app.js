/* Include Express, make a router and an app */
const express = require('express');
const app = express();

/* Express protection and utility */
const ExpressUtility = {
    helmet: require('helmet'),
    body_parser: require('body-parser')
}
app.use(ExpressUtility.helmet());
app.use(ExpressUtility.body_parser.json({ type: 'application/json' }));

/* Include configuration */
const config = require('./config.json');

// API
const api = require('./src/api');
app.use("/api/v1", api)

app.use("/", (req, res) => {
    res.send(`Welcome to ${config.name}'s website${req.method != "GET" ? ` - ${req.method} request` : ""}`);
    res.end();
});

app.listen(config.http.port, () => {
    console.log(`Listening on http://*:${config.http.port}`);
});