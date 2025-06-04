const express = require('express');
const cors = require('cors');
const { MongoClient } = require('mongodb');

const app = express();
const PORT = 4000;
app.use(cors());

const uri = "mongodb://localhost:27017";
const client = new MongoClient(uri);

app.get('/data', async (req, res) => {
  try {
    await client.connect();
    const db = client.db('mads_stage2025a');
    const collection = db.collection('Data_Questionnaire_CN');
    const data = await collection.find({}).toArray();
    
        // Reformater le champ Horodateur (format FR -> ISO)
    const formattedData = data.map(doc => {
      if (doc.Horodateur && typeof doc.Horodateur === 'string') {
        const match = doc.Horodateur.match(/^(\d{2})\/(\d{2})\/(\d{4}) (\d{2}:\d{2}:\d{2})$/);
        if (match) {
          const [_, day, month, year, time] = match;
          doc.Horodateur = new Date(`${year}-${month}-${day}T${time}`).toISOString();
        }
      }
      
      // scoreKPI
      let score = 0;
      const valueMap = (val, map) => map[val?.toLowerCase()] ?? 0;
      
      // Règles de score
      score += valueMap(doc["Niveau lubrifiant"], { "haut": 2, "moyen": 1, "bas": 0 });
      score += valueMap(doc["Niveau d'huile"], { "haut": 2, "moyen": 1, "bas": 0 });
      score += valueMap(doc["Remplissage bac copeaux"], { "haut": 0, "moyen": 0.5, "bas": 1 });
      score += valueMap(doc["Tiroir haut desserte"], { "complet": 1, "manquant": 0 });
      score += valueMap(doc["Propreté zone d'usinage"], { "propre": 1, "moyen": 0.5, "non nettoyé": 0 });
      score += valueMap(doc["Propreté machine"], { "propre": 1, "moyen": 0.5, "non nettoyé": 0 });

      // Température
      const temp = parseFloat(doc["Température bloc froid (en °C)"]);
        if (!isNaN(temp) && temp < 30) {
          score += 2;
        }

      // Ajouter le scoreKPI au doc
      doc.scoreKPI = score;
      
      return doc;
    });

    res.json(formattedData);
  } catch (error) {
    console.error(error);
    res.status(500).send('Erreur serveur');
  }
});

app.listen(PORT, () => {
  console.log(`API en écoute sur http://localhost:${PORT}`);
});
