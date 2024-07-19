const express = require('express');
const app = express();
const bodyParser = require('body-parser');
const path = require('path');
const port = process.env.PORT || 3333;
const cors = require('cors');
const ngrok = require('ngrok');

// Serve static files from the 'public' directory
app.use('/public', express.static(path.join(__dirname, 'public')));

// Middleware to parse URL-encoded bodies
app.use(bodyParser.urlencoded({ extended: false }));

// Enable CORS for all origins
app.use(cors());

// Serve the main HTML file
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'views', 'index.html'));
});

// Start the server
app.listen(port, async () => {
    console.log(`Server is running at http://localhost:${port}`);
    
    // Optionally, start ngrok here
    const url = await ngrok.connect(port);
    console.log(`ngrok tunnel opened at: ${url}`);
});
