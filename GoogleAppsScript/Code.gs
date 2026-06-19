function doPost(e){

  var sheet = SpreadsheetApp.getActiveSpreadsheet().getActiveSheet();

  var data = JSON.parse(e.postData.contents);

  // Add header if empty
  if(sheet.getLastRow() == 0){
    sheet.appendRow(["Student Name","Book","Action","Remaining","Time"]);
  }

  sheet.appendRow([
    data.s,
    data.b,
    data.a,
    data.r,
    new Date()
  ]);

  return ContentService.createTextOutput("OK");
}

function doGet(){
  return ContentService.createTextOutput("Web App Running");
}
