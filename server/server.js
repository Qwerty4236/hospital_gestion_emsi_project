const express = require('express');
const db = require('./db');
const app = express();

app.use(express.json());

// Add a name
app.post('/names', (req, res) => {
  const { name,ip } = req.body;
  db.run('INSERT INTO names (name,ip) VALUES (?,?)', [name,ip], function (err) {
    if (err) return res.status(500).json({ error: err.message });
    res.status(201).type("text/plain").send(String(this.lastID));
  });
});

// Get all names
app.get('/names', (req, res) => {
    db.all('SELECT * FROM names ORDER BY id ASC', [], (err, rows) => {
      if (err) return res.status(500).json({ error: err.message });
      const bb=rows.map(x=>{
        return `${x.id} ${x.name} ${x.ip} ${x.created_at.split(" ").join("/")}`
      }).join('\n')
      res.type("text/plain").send(bb)
    });
  }
);

// Delete a name by ID
app.delete('/names/:id', (req, res) => {
    const { id } = req.params;
    db.run('DELETE FROM names WHERE id = ?', [id], function (err) {
      if (err) return res.status(500).json({ error: err.message });
      res.json({ deleted: this.changes });
    });
  }
);

app.get('/numbers', (req, res) => {
  db.all('SELECT * FROM names ORDER BY id ASC', [], (err, rows) => {
    if (err) return res.status(500).json({ error: err.message });
    res.json(rows.length);
  });
});


app.listen(3000, () => {
  console.log('✅ SQLite API running at http://localhost:3000');
});
