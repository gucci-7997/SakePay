function doGet(e) {
  const url = "https://docs.google.com/spreadsheets/d/1kDgjPH-jsFXTsXAlwqQ_dJcZYoQL3zSoMhe71coTd6A/edit?gid=0#gid=0";
  const ss = SpreadsheetApp.openByUrl(url);
  const sheet = ss.getSheets()[0];
  const params = {
    "timestamp": new Date(),
    "id": e.parameter.id,
    "weight": e.parameter.weight
  };
  sheet.appendRow(Object.values(params));
  return ContentService.createTextOutput('done');
}
