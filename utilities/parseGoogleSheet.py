from __future__ import print_function
import pickle
import os.path
from googleapiclient.discovery import build
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request
import json

SCOPES = ['https://www.googleapis.com/auth/spreadsheets.readonly']

SPREADSHEET_ID = ''
START_ROW = 1
RANGE_NAME = 'book1!A2:G'  # todo fill this data dynamic!

def getSpreadSheetId():
    with open('parseSettings.json') as json_file:
        data = json.load(json_file)
        if not data['spreadsheetId']:
            print("spreadsheetId is not valid!")
        return data['spreadsheetId']

def getStartRow():
    with open('parseSettings.json') as json_file:
        data = json.load(json_file)
        if not data['startRow']:
            print("startRow is not valid!")
        return data['startRow']

def parseSheet(spreadsheetId, startRow):
    with open('parseSettings.json') as json_file:
        data = json.load(json_file)
    for page in data['pages']:
        print('sheet: ' + page['sheet'])
        print('output: ' + page['output'])

def parseData():
    creds = None
    if os.path.exists('token.pickle'):
        with open('token.pickle', 'rb') as token:
            creds = pickle.load(token)
    if not creds or not creds.valid:
        if creds and creds.expired and creds.refresh_token:
            creds.refresh(Request())
        else:
            flow = InstalledAppFlow.from_client_secrets_file(
                'credentials.json', SCOPES)
            creds = flow.run_local_server(port=0)
        with open('token.pickle', 'wb') as token:
            pickle.dump(creds, token)

    service = build('sheets', 'v4', credentials=creds)

    # Call the Sheets API
    sheet = service.spreadsheets()
    result = sheet.values().get(spreadsheetId=SPREADSHEET_ID,
                                range=RANGE_NAME).execute()
    values = result.get('values', [])

    if not values:
        print('No data found.')
    else:
        print('Name, Major:')
        for row in values:
            print('%s, %s' % (row[0], row[4]))

def main():
    spreadsheetId = getSpreadSheetId()
    # print('%s' % (spreadsheetId))
    startRow = getStartRow()
    # print('%s' % (startRow))
    parseSheet(spreadsheetId, startRow)

if __name__ == '__main__':
    main()