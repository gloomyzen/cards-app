from __future__ import print_function
import pickle
import os.path
from googleapiclient.discovery import build
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request
import json

SCOPES = ['https://www.googleapis.com/auth/spreadsheets.readonly']


def getSpreadSheetId():
    with open('parseSettings.json') as json_file:
        data = json.load(json_file)
        if not data['spreadsheetId']:
            print("spreadsheetId is not valid!")
        return data['spreadsheetId']


def getFindRange():
    with open('parseSettings.json') as json_file:
        data = json.load(json_file)
        if not data['findDiapason']:
            print("findDiapason is not valid!")
        return data['findDiapason']


def getDataStruct():
    struct = list()
    with open('parseSettings.json') as json_file:
        data = json.load(json_file)
        for page in data['dataStruct']:
            # struct.append({'index':page['index'], 'output':page['output']})
            struct.append(page)
        return struct


def parseSheet(spreadsheetId, findRange, dataStruct):
    with open('parseSettings.json') as json_file:
        data = json.load(json_file)
    for page in data['pages']:
        sheetName = page['sheet']
        outputFilePath = page['output']
        currentRange = sheetName + '!' + findRange
        # print('currentRange: ' + currentRange)
        # print('len: %s' % (len(dataStruct)))
        parseData(spreadsheetId, currentRange, dataStruct, outputFilePath)


def parseData(spreadsheetId, findRange, dataStruct, outputFilePath):
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
    result = sheet.values().get(spreadsheetId=spreadsheetId,
                                range=findRange).execute()
    values = result.get('values', [])

    jsonData = []
    if not values:
        print('No data found.')
    else:
        for item in values:
            jsonRow = {}
            for row in dataStruct:
                index = row['index']
                try:
                    jsonRow.update({row['output']: item[index]})
                except:
                    jsonRow.update({row['output']: ''})

            print(jsonRow)
            jsonData.append(jsonRow)

    with open(outputFilePath, 'w') as outfile:
        json.dump(jsonData, outfile)

def main():
    spreadsheetId = getSpreadSheetId()
    # print('%s' % (spreadsheetId))
    findRange = getFindRange()
    # print('%s' % (startRow))
    dataStruct = getDataStruct()
    parseSheet(spreadsheetId, findRange, dataStruct)


if __name__ == '__main__':
    main()
