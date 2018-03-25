
int iniWifi(){
  int wif=0;
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,1);
  display.println("Connectant al WIFI: ");
  #if DEBUG==1
    display.println(ssid);
  #endif
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    display.print(".");
    display.display();
    wif++;
    if (wif > 100 ) {
      Error("No es pot connectar  al WIFI",0);
      return 0;
    }
  }
  #if DEBUG==1 
    display.clearDisplay();
    display.setCursor(0,1);
    display.print("Connectat: ");  
    display.println(ssid);  
    display.print("IP: ");
    display.println(WiFi.localIP());
    display.display();
    display.print("Servidor:");
    display.println(server_addr);
    display.display();
    ok();
    delay(1000);
  #endif
  return 1;
}

int ConnexioMysql(){
  if (!conn.connect(server_addr, 3306, user, password)) {
    Error("No es pot connectar ala BBDD.",1);
    conn.close();
    return 0;
  }else{
    return 1;
  }
}

void InsertMysql(String table){
  String INSERT_SQL = "INSERT INTO Finger.";
  char query[60];
  INSERT_SQL=INSERT_SQL + table + " (User,Classroom) VALUES ("; 
  INSERT_SQL=INSERT_SQL + ID + ",'"; 
  INSERT_SQL=INSERT_SQL + AULA + "')"; 
  INSERT_SQL.toCharArray(query,60);
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  if (cur_mem->execute(query)){
    delete cur_mem;
    #if DEBUG==1 
      Missatge("Inserit",0,42);  
    #endif
  }else{
    Error("No es pot inserir a  la base de dades",1);
  }
}

String ConsultaMysql(){
  row_values *row = NULL;
  String SQL = "SELECT Name FROM Finger.User WHERE User=";
  char query[70];
  SQL=SQL + ID + " AND Classroom='"; 
  SQL=SQL + AULA + "'"; 
  SQL.toCharArray(query,70);
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  if (cur_mem->execute(query)){
    column_names *columns = cur_mem->get_columns();
    row = cur_mem->get_next_row();
    if (row != NULL) {
      name = row->values[0];
    }else{
      name="NO";
    }
    #if DEBUG==1 
      Missatge("Consultat",0,52);      
    #endif
    delete cur_mem;
    return name;      
  }else{
    Error("No es pot consultar ala base de dades",1);
    return "NO";
  }
}

/*
void InsertMysql(String fexa){
  String INSERT_SQL = "INSERT INTO finger.finger (Aula,Template) VALUES ('";
  char query[1085];
  INSERT_SQL=INSERT_SQL + AULA + "','"; 
  INSERT_SQL=INSERT_SQL + fexa + "')"; 
  INSERT_SQL.toCharArray(query,1085);
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  if (cur_mem->execute(query)){
    delete cur_mem;
    Missatge("Inserit",0,42);  
  }else{
    Error("No es pot inserir a  la base de dades",1);
  }
}
*/


