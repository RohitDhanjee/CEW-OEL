#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h> //For Fetch the API
#include <cJSON.h>
#include <time.h>
#include <float.h> // For DBL_MAX
#include <math.h> // For fabs
#include "email_sender.h" // For Email Sending

struct MemoryStruct {
    char *memory;
    size_t size;
};

size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (ptr == NULL) {
        printf("Not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

//static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *userp); (ForEMAIL)
static size_t read_callback(void *ptr, size_t size, size_t nmemb, FILE *stream);

// Function to read data from the file for CURLOPT_READFUNCTION 
size_t read_callback(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    return fread(ptr, size, nmemb, stream);
}

// Function to send email with attachment
int send_email_with_attachment(const char *to, const char *cc, const char *file_path) {
    CURL *curl;
    CURLcode res = CURLE_OK;

    FILE *file = fopen(file_path, "rb");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", file_path);
        return 1;
    }

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        struct curl_slist *recipients = NULL;

        // Specify email server details
        curl_easy_setopt(curl, CURLOPT_URL, "smtps://smtp.gmail.com");
        curl_easy_setopt(curl, CURLOPT_USERPWD, "rohitdhanjee25@gmail.com:orpgmgqiiaiqmqpm");
        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);

        // Add email recipients
        if (to)
            recipients = curl_slist_append(recipients, to);
        if (cc)
            recipients = curl_slist_append(recipients, cc);
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        // Set the read callback function to read the file content
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
        curl_easy_setopt(curl, CURLOPT_READDATA, file);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        // Perform the email sending
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        // Clean up
        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }

    // Close the file
    fclose(file);

    curl_global_cleanup();
    return (int)res;
}

int main() {
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();

    if (curl) {
        struct MemoryStruct chunk;
        chunk.memory = malloc(1);
        chunk.size = 0;

        time_t current_time = time(NULL);
        struct tm *local_time = localtime(&current_time);
        char current_date[20];
        strftime(current_date, sizeof(current_date), "%Y-%m-%d", local_time);

        char url[300];

        for (int i = 0; i < 3; ++i) {
    	time_t timestamp = current_time - (i * 24 * 60 * 60);
    	struct tm *previous_day = localtime(&timestamp);
    	char date[20];
    	strftime(date, sizeof(date), "%Y-%m-%d", previous_day);

    	sprintf(url, "http://api.weatherapi.com/v1/history.json?key=c107069054874fcaa93182210240501&q=karachi&dt=%s", date);
    	curl_easy_setopt(curl, CURLOPT_URL, url);
    	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
    	res = curl_easy_perform(curl);

    if (res == CURLE_OK) {
        char filename[50];
        sprintf(filename, "historical_weather_%s.json", date); // Append date to filename

        FILE *fp = fopen(filename, "w");
        if (fp != NULL) {
            fwrite(chunk.memory, 1, chunk.size, fp);
            fclose(fp);
            printf("Data saved to '%s'\n", filename);
        } else {
            printf("Failed to create/open file for writing.\n");
        }
    } else {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }

    // Clear the memory chunk for the next iteration
    if (chunk.memory) {
        free(chunk.memory);
        chunk.memory = NULL;
        chunk.size = 0;
    }
}

curl_easy_cleanup(curl);
    }
    cJSON *all_raw_data = cJSON_CreateArray();

    time_t current_time = time(NULL);
        struct tm *local_time = localtime(&current_time);
        char current_date[20];
        strftime(current_date, sizeof(current_date), "%Y-%m-%d", local_time);
    for (int i = 0; i < 3; ++i) {
            time_t timestamp = current_time - (i * 24 * 60 * 60);
            struct tm *previous_day = localtime(&timestamp);
            char date[20];
            char filename[50];
            strftime(date, sizeof(date), "%Y-%m-%d", previous_day);
            sprintf(filename, "historical_weather_%s.json", date); // Append date to filename
	FILE *file = fopen(filename, "r");
    	if (file == NULL) {
        printf("Unable to open file for reading.\n");
        return 1;
    	}

    	// Get the file size
    	fseek(file, 0, SEEK_END);
    	long file_size = ftell(file);
    	rewind(file);

    	// Allocate memory to read the entire file
    	char *json_buffer = (char *)malloc(file_size + 1);
    	if (json_buffer == NULL) {
        	printf("Memory allocation failed.\n");
        	fclose(file);
        	return 1;
    	}

    	// Read the file content into the buffer
    	size_t read_size = fread(json_buffer, 1, file_size, file);
    	if (read_size != file_size) {
        	printf("Reading file failed.\n");
        	fclose(file);
        	free(json_buffer);
        	return 1;
    	}
    	json_buffer[read_size] = '\0'; // Add null terminator at the end

    	fclose(file);

    	cJSON *json = cJSON_Parse(json_buffer);
    
    	if (json != NULL) {
        	cJSON *location = cJSON_GetObjectItemCaseSensitive(json, "location");
        	cJSON *forecast = cJSON_GetObjectItemCaseSensitive(json, "forecast");
        	cJSON *forecastday = cJSON_GetObjectItemCaseSensitive(forecast, "forecastday");
        	cJSON *day = cJSON_GetArrayItem(forecastday, 0);
        	cJSON *day_data = cJSON_GetObjectItemCaseSensitive(day, "day");

        	cJSON *raw_data = cJSON_CreateObject();
		if(i==0){
        		cJSON *name = cJSON_GetObjectItemCaseSensitive(location, "name");
        		cJSON *region = cJSON_GetObjectItemCaseSensitive(location, "region");
        		cJSON *country = cJSON_GetObjectItemCaseSensitive(location, "country");
        		cJSON *local_time = cJSON_GetObjectItemCaseSensitive(location, "localtime");
        		cJSON *hour = cJSON_GetObjectItemCaseSensitive(day, "hour");
	
			printf("\n");
        		//printf("Name: %s\n", name->valuestring);
        		//printf("Region: %s\n", region->valuestring);
        		//printf("Country: %s\n", country->valuestring);
        		//printf("Local Time: %s\n", local_time->valuestring);
        
				
			if (hour != NULL && cJSON_IsArray(hour)) {
			    //printf("Closest Hourly Forecast:\n");

    			    time_t current_epoch_time = time(NULL);
    			    double closest_time_difference = DBL_MAX; // Initialize with a large value
    			    cJSON *closest_hour_data = NULL;
    			    
			// Iterate through the "hour" array and print the "time" parameter

    			    int hour_array_size = cJSON_GetArraySize(hour);
    			    for (int i = 0; i < hour_array_size; i++) {
        			cJSON *hour_data = cJSON_GetArrayItem(hour, i);
        			cJSON *hour_time = cJSON_GetObjectItemCaseSensitive(hour_data, "time");

        			if (hour_time != NULL && cJSON_IsString(hour_time)) {
            				struct tm tm_hour = {0}; // Initialize tm_hour

            				int year, month, day, hour, minute;
            				if (sscanf(hour_time->valuestring, "%d-%d-%d %d:%d", &year, &month, &day, &hour, &minute) == 5) {
                			tm_hour.tm_year = year - 1900;
                			tm_hour.tm_mon = month - 1;
                			tm_hour.tm_mday = day;
                			tm_hour.tm_hour = hour;
                			tm_hour.tm_min = minute;
                			time_t hour_epoch_time = mktime(&tm_hour);

                			double time_difference = difftime(hour_epoch_time, current_epoch_time);
                			if (fabs(time_difference) < closest_time_difference) {
                    				closest_time_difference = fabs(time_difference);
                    				closest_hour_data = hour_data;
                				}
            				}
        			}
    			}

        		const char *nameString = cJSON_GetStringValue(name);
			cJSON_AddStringToObject(raw_data, "Name", nameString);

			const char *regionString = cJSON_GetStringValue(region);
			cJSON_AddStringToObject(raw_data, "Region", regionString);
	
			const char *countryString = cJSON_GetStringValue(country);
			cJSON_AddStringToObject(raw_data, "Country", countryString);
	
			const char *localtimeString = cJSON_GetStringValue(local_time);
			cJSON_AddStringToObject(raw_data, "Local Time", localtimeString);
			
    			if (closest_hour_data != NULL) {
        			cJSON *closest_hour_time = cJSON_GetObjectItemCaseSensitive(closest_hour_data, "time");
        			cJSON *temp_c = cJSON_GetObjectItemCaseSensitive(closest_hour_data, "temp_c");

        			//printf("Closest Time: %s\n", closest_hour_time->valuestring);
        			//printf("Temperature (C): %.2f\n", cJSON_GetNumberValue(temp_c));
        			const char *closest_time_String = cJSON_GetStringValue(closest_hour_time);
				cJSON_AddStringToObject(raw_data, "Closest Time", closest_time_String);
				cJSON_AddNumberToObject(raw_data, "Temp_C", cJSON_GetNumberValue(temp_c));
	
    				}	
			}
	
	cJSON_AddItemToArray(all_raw_data, raw_data);
	//printf("\n");
        		}
        

        cJSON *maxtemp_c = cJSON_GetObjectItemCaseSensitive(day_data, "maxtemp_c");
        cJSON *avgtemp_c = cJSON_GetObjectItemCaseSensitive(day_data, "avgtemp_c");
        cJSON *avghumidity = cJSON_GetObjectItemCaseSensitive(day_data, "avghumidity");
        cJSON *date = cJSON_GetObjectItemCaseSensitive(day, "date");

        //printf("Max Temp (C): %.2f\n", cJSON_GetNumberValue(maxtemp_c));
        //printf("Avg Temp (C): %.2f\n", cJSON_GetNumberValue(avgtemp_c));
        //printf("Avg Humidity: %d\n", avghumidity->valueint);
        //printf("Date: %s\n", date->valuestring);
	//printf("\n");
        
        
	
	const char *dateString = cJSON_GetStringValue(date);
	
	cJSON_AddStringToObject(raw_data, "Date", dateString);
        cJSON_AddNumberToObject(raw_data, "MaxTemp_C", cJSON_GetNumberValue(maxtemp_c));
        cJSON_AddNumberToObject(raw_data, "AvgTemp_C", cJSON_GetNumberValue(avgtemp_c));
        cJSON_AddNumberToObject(raw_data, "AvgHumidity", avghumidity->valueint);

        // Add the raw data JSON object to the array
        cJSON_AddItemToArray(all_raw_data, raw_data);
      
        cJSON_Delete(json);
        free(json_buffer);
    } else {
        printf("JSON parsing error for file content.\n");
        free(json_buffer);
        return 1;
    }}


    //Opening a Json File to write raw data.
    FILE *fp = fopen("all_raw_weather_data.json", "w");
    if (fp != NULL) {
        char *json_string = cJSON_Print(all_raw_data);
        if (json_string != NULL) {
            fwrite(json_string, 1, strlen(json_string), fp);
            fclose(fp);
            printf("All raw data saved to 'all_raw_weather_data.json'\n");
            free(json_string);
        } else {
            printf("Failed to convert data to JSON string.\n");
            fclose(fp);
        }
    } else {
        printf("Failed to create/open file 'all_raw_weather_data.json' for writing.\n");
    }

    // Delete the JSON array
    cJSON_Delete(all_raw_data);
    
    //Opening raw data file for processing.
    FILE *file_all_raw_data = fopen("all_raw_weather_data.json", "r");
    if (file_all_raw_data == NULL) {
        printf("Unable to open 'all_raw_weather_data.json' for reading.\n");
        return 1;
    }

    fseek(file_all_raw_data, 0, SEEK_END);
    long file_size_all_raw_data = ftell(file_all_raw_data);
    rewind(file_all_raw_data);

    char *json_buffer_all_raw_data = (char *)malloc(file_size_all_raw_data + 1);
    if (json_buffer_all_raw_data == NULL) {
        printf("Memory allocation failed.\n");
        fclose(file_all_raw_data);
        return 1;
    }

    size_t read_size_all_raw_data = fread(json_buffer_all_raw_data, 1, file_size_all_raw_data, file_all_raw_data);
    if (read_size_all_raw_data != file_size_all_raw_data) {
        printf("Reading 'all_raw_weather_data.json' failed.\n");
        fclose(file_all_raw_data);
        free(json_buffer_all_raw_data);
        return 1;
    }
    json_buffer_all_raw_data[read_size_all_raw_data] = '\0';

    fclose(file_all_raw_data);

    cJSON *json_all_raw_data = cJSON_Parse(json_buffer_all_raw_data);
    if (json_all_raw_data == NULL) {
        printf("JSON parsing error for 'all_raw_weather_data.json' content.\n");
        free(json_buffer_all_raw_data);
        return 1;
    }
//Initializing arrays and variable for Average Calculations and Loaction Details.

    int array_size = cJSON_GetArraySize(json_all_raw_data);
    float max_temp_c_values[array_size];
    float avg_temp_c[array_size];
    int avg_humidity_values[array_size];
    float close_temp;
    float avg_temp[array_size];
    float avg=0.0;
    int avg_h=0;
    float total_avg;
    int total_avg_h;
    
    typedef struct {
        const char *name;
        const char *region;
        const char *country;
        const char *local_time;
    } Location;

    Location locations[array_size];

        
    for (int i = 0; i < array_size; ++i) {
        cJSON *item = cJSON_GetArrayItem(json_all_raw_data, i);
        cJSON *name = cJSON_GetObjectItemCaseSensitive(item, "Name");
        cJSON *region = cJSON_GetObjectItemCaseSensitive(item, "Region");
        cJSON *country = cJSON_GetObjectItemCaseSensitive(item, "Country");
	cJSON *local_time = cJSON_GetObjectItemCaseSensitive(item, "Local Time");
        cJSON *temp_c= cJSON_GetObjectItemCaseSensitive(item, "Temp_C");
        cJSON *max_temp = cJSON_GetObjectItemCaseSensitive(item, "MaxTemp_C");
        cJSON *avg_humidity = cJSON_GetObjectItemCaseSensitive(item, "AvgHumidity");
        cJSON *avg_temp = cJSON_GetObjectItemCaseSensitive(item, "AvgTemp_C");

        if (cJSON_IsString(name) && cJSON_IsString(region) && cJSON_IsString(country)) {
            locations[i].name = cJSON_GetStringValue(name);
            locations[i].region = cJSON_GetStringValue(region);
            locations[i].country = cJSON_GetStringValue(country);
            locations[i].local_time = cJSON_GetStringValue(local_time);

        }
        
        
	//if (temp_c!=NULL){
	//close_temp = cJSON_GetNumberValue(temp_c);
	//printf("Close Temp (C) %d: %.2f\n", i + 1, close_temp);
	//}
        max_temp_c_values[i] = cJSON_GetNumberValue(max_temp);
        avg_humidity_values[i] = cJSON_GetNumberValue(avg_humidity);
        avg_temp_c[i] = cJSON_GetNumberValue(avg_temp);
        
        //printf("Max Temp (C) %d: %.2f\n", i + 1, max_temp_c_values[i]);
        //printf("Avg Humidity %d: %d\n", i + 1, avg_humidity_values[i]);
        //printf("Avg Temp (C) %d: %.2f\n", i + 1, avg_temp_c[i]);
         
    }
    
    //Running loop for average Calculations on Arrays values.
    for (int i=0; i<3; i++){
    avg+=avg_temp_c[i];
    //printf("%.1f\n",avg);
    avg_h+=avg_humidity_values[i];
    total_avg=(avg/3);
    total_avg_h=(avg_h/3);}
    
    
    //printf("%f",total_avg);
   // printf("humidty= %d",total_avg_h);
   // printf("Close Temp (C) 1: %.2f\n", close_temp);
    
    //Opening a file to save Processed data "Environmental Report" 
    FILE *filePointer; // File pointer
    
    
    // Open the file in write mode
    filePointer = fopen("Environmental_report.txt", "w");
    
    // Check if the file opened successfully
    if (filePointer == NULL) {
        printf("Unable to open the file.\n");
        return 1; // Exit the program if unable to open the file
    }
    
    // Write the strings into the file using fprintf()
    
    fprintf(filePointer,"\n-----Environmental Report !!-----\n");
    fprintf(filePointer,"\n---> LOCATION:\n");
    fprintf(filePointer,"-> Name: %s\n", locations[0].name);
    fprintf(filePointer,"-> Region: %s\n", locations[0].region);
    fprintf(filePointer,"-> Country: %s\n", locations[0].country);
    fprintf(filePointer,"-> Local Time: %s\n", locations[0].local_time);
    fprintf(filePointer,"\n---> TEMPERATURE\n");
    
    //Checks weather conditions After calculation of 3 days averege data's
    if (total_avg < 25 && total_avg>15){
    
    fprintf(filePointer,"\n-> The temperature is within the range of 15C to 25C.\n"
);
	fprintf(filePointer,"-> Message: Cool Day! You Should wear warm Clothes.\n");}
	else if (total_avg < 15 && total_avg>10){fprintf(filePointer,"-> The temperature is within the range of 10C to 15C.\n"
);fprintf(filePointer,"-> Message: ITS COOL OUTSIDE...You Should wear warm Clothes.\n");
	}
	else if (total_avg < 10 ){fprintf(filePointer,"-> The temperature is below 10C.\n"
);fprintf(filePointer,"-> Message: ITS VERY COOL OUTSIDE...You Should wear warm Clothes To PROTECT yourself...\n");}
	else if (total_avg > 25 && total_avg<30){fprintf(filePointer,"-> The temperature is within the range of 30C to 25C.\n"
);fprintf(filePointer,"-> Message: AVERAGE TEMPERATURE..ENJOY!!\n");}
	else if (total_avg > 30){fprintf(filePointer,"-> The temperature is above 30C.\n"
);fprintf(filePointer,"-> Message: HOT DAY.. STAY HYDRATED!!\n");}



fprintf(filePointer,"\n---> HUMIDITY\n");
    if (total_avg_h < 60 && total_avg_h>40){
    
    	fprintf(filePointer,"\n-> The Humidity is within the range of 60 to 40. \n");
	fprintf(filePointer,"-> Message: Humidity levels are stable and within the optimal range\n");}
	
	else if (total_avg_h < 40 ){
	fprintf(filePointer,"\n-> The Humidity is below 40. \n");
	fprintf(filePointer,"-> Message: Dry conditions observed; ensure adequate moisture in the environment.\n");}
	
	else if (total_avg_h > 60){
	fprintf(filePointer,"\n-> The Humidity is above 60 .\n");
	fprintf(filePointer,"-> Message: Humidity is above optimal levels; take precautions to maintain a comfortable environment.\n");}

    // Close the file
    fclose(filePointer);
    
    printf("\nEnvironmental Report successfully generated.\n");
    cJSON_Delete(json_all_raw_data);
    free(json_buffer_all_raw_data);
    
    
    
    // Implementation of send_email_with_attachment
    const char *recipient_email = "rohitsanjot25@gmail.com";
    const char *cc_email = "rohitsanjot25@gmail.com";
    const char *attachment_path = "Environmental_report.txt";

    int result = send_email_with_attachment(recipient_email, cc_email, attachment_path);

    if (result == 0) {
        printf("\nEmail sent successfully!\n");
    } else {
        printf("\nFailed to send email.\n");
    }

    return 0;
}
