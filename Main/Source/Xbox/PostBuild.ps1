echo "Copying libs..."

$LibDir = "../../../Lib/Xbox"

# Copy all .lib files to $(ZEDPATH)/Libs
$LibFiles = $LibDir + "/*.lib"

# Make damn sure that the *.lib files exist
$LibFilesExist = Test-Path $LibFiles
If( $LibFilesExist -eq $False )
{
    echo "[ERROR] Library files not found"
    return
}

# Copy the *.lib files out
$OutDir = "$env:ZEDPATH/Lib/Xbox"
$OutExists = Test-Path $OutDir
If( $OutExists -eq $False )
{
    echo "Creating directory: $OutDir"
    mkdir -p $OutDir
}

# Get files (if available) from OutDir
$OutFiles = $OutDir + "/*.lib"

function Copy-LatestFile
{
    Param( $File1, $File2, [switch]$WhatIf )
    $File1Date = Get-Item $File1 | ForEach-Object{ $_.LastWriteTimeUTC }
    $File2Date = Get-Item $File1 | ForEach-Object{ $_.LastWriteTimeUTC }
    echo "F1" + $File1Date
        echo "F2" + $File2Date
        
    if( $File1Date -gt $File12Date )
    {
        if( $WhatIf )
        {
            Copy-Item -Path $File1 -Dest $File2 -Force -WhatIf
        }
        else
        {
            Copy-Item -Path $File1 -Dest $File2 -Force
        }
    }
    Write-Host
}

# Compare the two *.lib trees, if any files in the destination directory are
# older than in the compile directory, copy the compiled ones over.

echo $OutFiles
echo $LibFiles
Copy-LatestFile $LibFiles $LibFiles

echo "Success"
