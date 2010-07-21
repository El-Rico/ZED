echo "Copying headers..."

# Functions
function CWD
{
    (Get-Location).Path.Split("\")[(Get-Location).Path.Split("\").Length -1]
}

# Use for copying files over at the end
$CurrDir = CWD
echo $CurrDir

# Check that the *.hpp files exist in Headers (first check for ./Headers)
$CheckDir = "./Headers"
$DirExists = Test-Path $CheckDir

If( $DirExists -eq $False )
{
    echo "[ERROR] No headers to copy"
    return
}

$Files = "./Headers/*.hpp"
$FilesExist = Test-Path $Files

if( $FilesExist -eq $False )
{
    echo "[ERROR] No headers found in directory"
    return
}

$OutDir = "$env:ZEDPATH\Include\Xbox\" + $CurrDir
$DirExists = Test-Path $OutDir

If($DirExists -eq $False)
{
    echo "Creating directory: $OutDir"
    mkdir -p $OutDir
}

cp ./Headers/*.hpp $OutDir
