import gspread
import pandas as pd
from pymongo import MongoClient
from pymongo.errors import DuplicateKeyError
from pathlib import Path
import os

# 🔹 Connexion à Google Sheets via la clé de service
# Path to the Google service account credentials. This can be overridden with
# the ``GFORM_CREDENTIALS`` environment variable to avoid hard coded absolute
# paths.
credentials_path = os.environ.get(
    "GFORM_CREDENTIALS",
    Path(__file__).with_name("questionnaire-gform-b04f6f13cdb7.json"),
)

gc = gspread.service_account(filename=str(credentials_path))

# 🔹 Ouverture du Google Sheet
sh = gc.open("Questionnaire CN - Réponses pour récupération de données")
worksheet = sh.worksheet("Réponses au formulaire 1")

# 🔹 Récupération des données
data = worksheet.get_all_records()
df = pd.DataFrame(data)

print("📄 Données récupérées depuis Google Sheets :")
print(df.head())

# 🔹 Connexion MongoDB
client = MongoClient("mongodb://localhost:27017/")
db = client["mads_stage2025a"]
collection = db["Data_Questionnaire_CN"]

# 🔹 Créer un index unique sur un champ identifiant (ex: Timestamp)
collection.create_index("Horodateur", unique=True)

# 🔹 Insertion avec gestion des doublons
inserted = 0
for row in data:
    try:
        collection.insert_one(row)
        inserted += 1
    except DuplicateKeyError:
        pass  # Ligne déjà insérée

print(f"✅ {inserted} nouvelle(s) ligne(s) insérée(s) dans MongoDB.")
