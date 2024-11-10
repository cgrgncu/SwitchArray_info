# PHP部分

```php
<?php
//**************************************************************************
//* Name: upload_v297csv_json_zip.php v2024110a
//* Copyright:
//* Author: HsiupoYeh
//* Version: v2024110a
//* Description: 上傳*.v297csv.zip檔案與對應的JSON檔案，驗證MD5成功後才儲存在指定資料夾。
//**************************************************************************

//--------------------------------------------------------------------------
// 使用者訪問:「../upload_v297csv_json_zip.php?show_form=true」網址時，會展示
// 瀏覽器上測試用的上傳表單。
//--
// 如果找到GET方法中有指定內容時，顯示上傳表單。
if (isset($_GET['show_form']) && $_GET['show_form']=='true') 
{
?>
<!-- 測試用的表單不做過多排版 -->
<!-- 表單開始 -->
<!-- 
「form」裡的「action」表示要提交表單的目標網址 
「form」裡的「method」填「post」表示要用POST方法提交表單
「form」裡的「enctype」填「multipart/form-data」表示傳輸檔案
 以上三項都是標準被規定要填的內容 
-->
-------------------------------------------------
<br>
<form action="upload_v297csv_json_zip.php" method="post" enctype="multipart/form-data">
	<!-- 
	「input」裡的「type」是告訴瀏覽器該準備怎樣的輸入項目。
	「input」裡的「value」是告訴瀏覽器該準備怎樣的輸入項目裡面要填什麼內容，若不填瀏覽器自動塞入預設值。
	例如: 
	<input type="submit" value="按我上傳檔案"/> 
	這表示產生一個提交表單用的按鈕，按鈕內顯示的文字是「按我上傳檔案」。
	-->
	<!-- 「input」裡的「name」是提交表單時的變數名稱，這個才會被伺服器端取得 -->
	
	<!-- 讓使用者可以選擇檔案的按鈕 -->
	讓使用者可以選擇JSON檔案的按鈕: <input type="file" name="v297csv_json_zip_file[]">
	<br><br>
	讓使用者可以選擇ZIP檔案的按鈕: <input type="file" name="v297csv_json_zip_file[]">
	<br><br>
	<!-- 提交用的按鈕 -->
	提交用的按鈕: <input type="submit" value="按我上傳檔案">
</form>
-------------------------------------------------
<br>
<!-- 表單結束 -->
<?php
}
//--------------------------------------------------------------------------

$debug_show=false;//測試開發時可以改成 true，看更多資訊。實際使用請設為 false。
//=============================================================
// 取得上傳檔案資訊
//-------------------------------------------------------------
// $_FILES是全域變數，是兩層的陣列，
// 第二層可以用 "name"、"type"、"size"、"tmp_name"、"error"
// 例如: 
// $_FILES["v297csv_json_zip_file"]["name"]
// $_FILES["v297csv_json_zip_file"]["type"]
// $_FILES["v297csv_json_zip_file"]["size"]
// $_FILES["v297csv_json_zip_file"]["tmp_name"]
// $_FILES["v297csv_json_zip_file"]["error"]
//--

// 如果POST方法的請求中有指定的內容時，就工作
if (isset($_FILES["v297csv_json_zip_file"]["name"]) &&
 count($_FILES["v297csv_json_zip_file"]["name"])==2 && 
 pathinfo($_FILES["v297csv_json_zip_file"]["name"][0], PATHINFO_EXTENSION)=="json" && 
 pathinfo($_FILES["v297csv_json_zip_file"]["name"][1], PATHINFO_EXTENSION)=="zip")
{
	if ($debug_show)echo '$_FILES["v297csv_json_zip_file"]["name"][0] = '.$_FILES["v297csv_json_zip_file"]["name"][0].'<br>';
	if ($debug_show)echo '$_FILES["v297csv_json_zip_file"]["type"][0] = '.$_FILES["v297csv_json_zip_file"]["type"][0].'<br>';
	if ($debug_show)echo '$_FILES["v297csv_json_zip_file"]["size"][0] = '.$_FILES["v297csv_json_zip_file"]["size"][0].'<br>';
	if ($debug_show)echo '$_FILES["v297csv_json_zip_file"]["tmp_name"][0] = '.$_FILES["v297csv_json_zip_file"]["tmp_name"][0].'<br>';
	if ($debug_show)echo '$_FILES["v297csv_json_zip_file"]["error"][0] = '.$_FILES["v297csv_json_zip_file"]["error"][0].'<br>';
	if ($debug_show)echo '--<br>';
	if ($debug_show)echo '$_FILES["v297csv_json_zip_file"]["name"][1] = '.$_FILES["v297csv_json_zip_file"]["name"][1].'<br>';
	if ($debug_show)echo '$_FILES["v297csv_json_zip_file"]["type"][1] = '.$_FILES["v297csv_json_zip_file"]["type"][1].'<br>';
	if ($debug_show)echo '$_FILES["v297csv_json_zip_file"]["size"][1] = '.$_FILES["v297csv_json_zip_file"]["size"][1].'<br>';
	if ($debug_show)echo '$_FILES["v297csv_json_zip_file"]["tmp_name"][1] = '.$_FILES["v297csv_json_zip_file"]["tmp_name"][1].'<br>';
	if ($debug_show)echo '$_FILES["v297csv_json_zip_file"]["error"][1] = '.$_FILES["v297csv_json_zip_file"]["error"][1].'<br>';
	if ($debug_show)echo '--<br>';
}
else
{
    if ($debug_show)echo '必須一次上傳兩個檔案到伺服器端!第一個檔案須為JSON檔，第二個檔案須為ZIP檔!<br>';
	$return_array["Return_Code"]='-1';
	$return_array["Description"]='必須一次上傳兩個檔案到伺服器端!第一個檔案須為JSON檔，第二個檔案須為ZIP檔!';
	echo json_encode($return_array,JSON_UNESCAPED_UNICODE);
	exit;	
}
//-------------------------------------------------------------
//=============================================================

//=============================================================
// 檢查存檔的資料夾是否可寫入
//-------------------------------------------------------------
$target_upload_folder_in_this_server = 'C:\R2MS_Lite_DataCenter';
if (is_writable($target_upload_folder_in_this_server)) 
{
    if ($debug_show) echo '伺服器端上傳的目標資料夾可以讀寫!<br>--<br>';
} 
else 
{
    if ($debug_show)echo '伺服器端上傳的目標資料夾不能讀寫!請通知管理員確認資料夾存在並且權限正確!<br>';
	$return_array["Return_Code"]='-1';
	$return_array["Description"]='伺服器端上傳的目標資料夾不能讀寫!請通知管理員確認資料夾存在並且權限正確!';
	echo json_encode($return_array,JSON_UNESCAPED_UNICODE);
	exit;
}
//-------------------------------------------------------------
//=============================================================

//=============================================================
// 檢查json內容
//-------------------------------------------------------------
$v297csv_json_str=file_get_contents($_FILES["v297csv_json_zip_file"]["tmp_name"][0]);
$v297csv_json_array = json_decode($v297csv_json_str, true);
// 檢查解析是否成功
if ($v297csv_json_array !== null ) 
{
	if ($debug_show)echo 'JSON檔案解析成功!<br>--<br>';
} 
else 
{
    if ($debug_show)echo 'JSON檔案解析失敗!<br>';
	$return_array["Return_Code"]='-1';
	$return_array["Description"]='JSON檔案解析失敗!';
	echo json_encode($return_array,JSON_UNESCAPED_UNICODE);
	exit;
}
//-------------------------------------------------------------
//=============================================================

//=============================================================
// 檢查上傳的ZIP檔案的尺寸
//-------------------------------------------------------------
if (isset($_FILES["v297csv_json_zip_file"]["size"][1]) && $_FILES["v297csv_json_zip_file"]["size"][1]>0) 
{
    if ($debug_show) echo '用戶提交的檔案大小>0!<br>';
	if (isset($v297csv_json_array["FileBytes"]) && $v297csv_json_array["FileBytes"]==$_FILES["v297csv_json_zip_file"]["size"][1])
	{
		if ($debug_show) echo '用戶提交的檔案通過Size驗證!<br>--<br>';
	}
	else
	{
		if ($debug_show) echo '用戶提交的檔案沒有通過Size驗證!檔案上傳不完全嗎?自提Size正確嗎?<br>';
		$return_array["Return_Code"]='-1';
		$return_array["Description"]='用戶提交的檔案沒有通過Size驗證!檔案上傳不完全嗎?自提Size正確嗎?';
		echo json_encode($return_array,JSON_UNESCAPED_UNICODE);
		exit;
	}
} 
else 
{
    if ($debug_show)echo '用戶提交的檔案大小為0!請確認上傳檔案是有內容的!<br>';
	$return_array["Return_Code"]='-1';
	$return_array["Description"]='用戶提交的檔案大小為0!請確認上傳檔案是有內容的!';
	echo json_encode($return_array,JSON_UNESCAPED_UNICODE);
	exit;
}
//-------------------------------------------------------------
//=============================================================

//=============================================================
// 檢查上傳檔案的MD5
//-------------------------------------------------------------
$file_md5_str_by_server="";
if (isset($_FILES["v297csv_json_zip_file"]["tmp_name"][1]) && $_FILES["v297csv_json_zip_file"]["size"]>0) 
{
    $temp_md5_str=@md5_file($_FILES["v297csv_json_zip_file"]["tmp_name"][1]);	
	if ($temp_md5_str==false)
	{
		//echo '檔案不存在!';
	}
	else
	{
		$file_md5_str_by_server=$temp_md5_str;
	}	
} 
//--
if ($debug_show)
{
	echo '$file_md5_str_by_server = '.$file_md5_str_by_server.'<br>';
	echo '--<br>';
}
//--
if (empty($file_md5_str_by_server))
{
	if ($debug_show) echo '用戶提交的檔案進行MD5計算失敗!請確認檔案是否存在!<br>';
	$return_array["Return_Code"]='-1';
	$return_array["Description"]='用戶提交的檔案進行MD5計算失敗!請確認檔案是否存在!';
	echo json_encode($return_array,JSON_UNESCAPED_UNICODE);
	exit;
}
elseif ($file_md5_str_by_server==$v297csv_json_array["FileMD5"])
{
	if ($debug_show) echo '用戶提交的檔案通過MD5驗證!<br>--<br>';
}
else
{
	if ($debug_show) echo '用戶提交的檔案沒有通過MD5驗證!檔案上傳不完全嗎?自提MD5碼正確嗎?<br>';
	$return_array["Return_Code"]='-1';
	$return_array["Description"]='用戶提交的檔案沒有通過MD5驗證!檔案上傳不完全嗎?自提MD5碼正確嗎?';
	echo json_encode($return_array,JSON_UNESCAPED_UNICODE);
	exit;
}
//-------------------------------------------------------------
//=============================================================

//=============================================================
// 搬移檔案到指定上傳目錄
//-------------------------------------------------------------
// 要上傳的目標資料夾
$target_folder=$target_upload_folder_in_this_server.DIRECTORY_SEPARATOR.
	'Projects'.DIRECTORY_SEPARATOR.$v297csv_json_array["ProjectName"].DIRECTORY_SEPARATOR.
	'Recorder'.DIRECTORY_SEPARATOR.$v297csv_json_array["ProfileName"].DIRECTORY_SEPARATOR.
	$v297csv_json_array["AcquisitionYear"].DIRECTORY_SEPARATOR.
	$v297csv_json_array["AcquisitionMonth"].DIRECTORY_SEPARATOR.
	$v297csv_json_array["AcquisitionDay"].DIRECTORY_SEPARATOR;
//-------------------------------------------------------------
//-------------------------------------------------------------
// 檢查資料夾存在
//--
if (!file_exists($target_folder))
{	
	if (!mkdir($target_folder, 0777, true)) 
	{
		if ($debug_show) echo '建立資料夾失敗!<br>';
		$return_array["Return_Code"]='-1';
		$return_array["Description"]='建立資料夾失敗!';
		echo json_encode($return_array,JSON_UNESCAPED_UNICODE);
		exit;
	}
}
//-------------------------------------------------------------
//-------------------------------------------------------------
// 檢查是否需要上傳
$need_upload=false;
if (file_exists($target_folder.$_FILES["v297csv_json_zip_file"]["name"][0]))
{
	$old_v297csv_json_str=file_get_contents($target_folder.$_FILES["v297csv_json_zip_file"]["name"][0]);
	$old_v297csv_json_array = json_decode($old_v297csv_json_str, true);
	// 檢查解析是否成功
	if ($old_v297csv_json_array !== null ) 
	{
		if ($debug_show)echo 'JSON檔案解析成功!<br>--<br>';
		if ($old_v297csv_json_array["FileUpload"]!="OK")
		{
			$need_upload=true;	
		};
	} 
	else 
	{
		if ($debug_show)echo 'JSON檔案解析失敗!<br>';
	}	
}
else
{
	$need_upload=true;	
}
//-------------------------------------------------------------
//-------------------------------------------------------------
// 上傳檔案
if ($need_upload)
{
	//-------------------------------------------------------------
	// 寫入新的JSON檔案	
	$v297csv_json_array["FileUpload"]="OK";//Ready=準備上傳，Fail=上傳失敗，OK=上傳成功
	file_put_contents($target_folder.$_FILES["v297csv_json_zip_file"]["name"][0],json_encode($v297csv_json_array,JSON_UNESCAPED_UNICODE));
	//--
	// 搬運檔案	
	if (move_uploaded_file($_FILES["v297csv_json_zip_file"]["tmp_name"][1],$target_folder.$_FILES["v297csv_json_zip_file"]["name"][1]))
	{
		if ($debug_show)echo '上傳成功!<br>';
		$return_array["Return_Code"]='0';
		$return_array["Description"]='上傳成功!';
		echo json_encode($return_array,JSON_UNESCAPED_UNICODE);
		exit;
	};
	//-------------------------------------------------------------
}
else
{
	if ($debug_show)echo '檔案存在!略過上傳!<br>';
	$return_array["Return_Code"]='1';
	$return_array["Description"]='檔案存在!略過上傳!';
	echo json_encode($return_array,JSON_UNESCAPED_UNICODE);
	exit;
}
//-------------------------------------------------------------

?>
```

### curl部分
```
curl.exe -F "v297csv_json_zip_file[]=@..\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\Recorder\XP1\2024\07\01\2001.json" -F "v297csv_json_zip_file[]=@..\[20240409A]Taiwan-Taipei-XiaoYouKengScenicPlatform(XYKP)\Recorder\XP1\2024\07\01\2001.zip" http://127.0.0.1/upload_v297csv/upload_v297csv_json_zip.php
PAUSE
```
