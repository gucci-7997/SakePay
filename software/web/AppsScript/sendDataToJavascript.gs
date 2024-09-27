function doGet() {
    const data = getData();
    const response = ContentService.createTextOutput();
    response.setMimeType(MimeType.JSON);
    response.setContent(JSON.stringify(data));
    return response;  
}

function getData() {
  const spreadsheet = SpreadsheetApp.getActiveSpreadsheet();
  const sheet = spreadsheet.getSheetByName('シート1');

  const values = sheet.getDataRange().getValues();

  const data = values.map(row => {
    let col = 0;
    return {
      timestamp: row[col++],
      id: row[col++],
      weight: row[col++],
    }
  });
  console.log(data);
  return data;
}