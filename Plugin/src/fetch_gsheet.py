import gspread
import json
from pathlib import Path
import os

# Determine the path to the credentials file. By default it is expected to live
# alongside this script and can be overridden using the ``GFORM_CREDENTIALS``
# environment variable.
credentials_path = os.environ.get(
    "GFORM_CREDENTIALS",
    Path(__file__).with_name("credentials.json"),
)

gc = gspread.service_account(filename=str(credentials_path))
sh = gc.open("Questionnaire CN - Réponses pour récupération de données")
worksheet = sh.worksheet("Réponses au formulaire 1")

rows = worksheet.get_all_records()
print(json.dumps(rows))  # Le script affiche le JSON sur stdout
