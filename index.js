const express = require('express');
const app = express();
const bodyParser = require('body-parser');
const path = require('path');
const port = process.env.PORT || 3333;

// Serve static files from the 'public' directory
app.use('/public', express.static(path.join(__dirname, 'public')));

// Middleware to parse URL-encoded bodies
app.use(bodyParser.urlencoded({ extended: false }));

// Serve the main HTML file
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'views', 'index.html'));
});

// Start the server
app.listen(port, () => {
    console.log(`Server is running at http://localhost:${port}`);
});
