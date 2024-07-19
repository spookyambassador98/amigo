const express = require('express');
const app = express();
const bodyparser = require('body-parser');
const path = require('path')
const port = process.env.PORT || 3333;

app.use('/public', express.static('public'));
app.use(bodyparser.urlencoded({ extended: false }));

app.get('/', (req, res) => {
    res.sendFile(__dirname + '/views/index.html');
});

app.listen(port, () => {
    console.log(`http://localhost:${port}`);
});
