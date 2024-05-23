void errorCommand(int* error_count,char command_read)
{
        (*error_count)++;
        Serial.println("!!!!!!!!!!!!!!!!!!");
        Serial.print("error count= ");
        Serial.println(*error_count);
        Serial.print("error type: command'");
        Serial.print(command_read);
        Serial.print("' is not a viable command, and its ASCII value is ");
        int junk=command_read;
        Serial.println(junk);
}