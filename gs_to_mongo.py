import gspread
import pandas as pd
from pymongo import MongoClient
from pymongo.errors import DuplicateKeyError

# 🔹 Connexion à Google Sheets via la clé de service
gc = gspread.service_account(filename="/home/mads/Devel/questionnaire_gform/questionnaire-gform-b04f6f13cdb7.json")

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
