from flask import Flask, render_template, request, redirect
import sqlite3

app = Flask(__name__)

# Configure SQLite database
conn = sqlite3.connect('birthdays.db', check_same_thread=False)
db = conn.cursor()

# Create table if it doesn't exist
db.execute("CREATE TABLE IF NOT EXISTS birthdays (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, month INTEGER, day INTEGER)")

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        # Get form data
        name = request.form.get('name')
        month = int(request.form.get('month'))
        day = int(request.form.get('day'))

        # Insert new birthday into the database
        db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", (name, month, day))
        conn.commit()

        # Redirect back to the index page
        return redirect('/')
    else:
        # Fetch all birthdays from the database
        db.execute("SELECT * FROM birthdays")
        birthdays = db.fetchall()

        # Render the index.html template with birthdays data
        return render_template('index.html', birthdays=birthdays)

if __name__ == '__main__':
    app.run(debug=True)
