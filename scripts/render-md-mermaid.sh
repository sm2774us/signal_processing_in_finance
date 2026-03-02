#!/usr/bin/env bash
# Usage: render-md-mermaid.sh document.md

markdown_input=$1
image_re=".*\.(svg|png)$"
echo "Markdown file: $markdown_input"
if [ "$1" == "" ]; then
  echo "Usage: $0 document.md"
  exit 1
fi

mermaid_config='{"flowchart": {"useMaxWidth": false }}'
mermaid_css='#container > svg { max-width: 100% !important; }'
echo "$mermaid_config" > .render-md-mermaid-config.json
echo "$mermaid_css" > .render-md-mermaid.css

mermaid_file=""
IFS=$'
'
# Extract image path and mermaid source using perl
for line in $(perl -0777 -ne 'while(m/!\[.*?\]\(([^\)]+)\)
+<details>([\s\S]*?)```mermaid
([\s\S]*?)
```/g){print "$1
$3
";} ' "$markdown_input")
do
    if [[ $line =~ $image_re ]]; then
        mermaid_file="$line.mermaid"
        # Ensure we have a path-like string
        if [[ ! "$mermaid_file" =~ ^.*/.* ]]; then
            mermaid_file="./$mermaid_file"
        fi
        mkdir -p -- "${mermaid_file%/*}"
        # Start a fresh mermaid file
        > "$mermaid_file"
    else
        # Append the line to the current mermaid file
        echo "$line" >> "$mermaid_file"
    fi
done

# Render all temporary mermaid files found
for mermaid_img in $(find . -name "*.mermaid" | sed -E 's/((.*).mermaid)/\2|\1/')
do
    image_file=${mermaid_img%|*}
    mermaid_file=${mermaid_img#*|}
    
    echo "Rendering $mermaid_file to $image_file..."
    
    # Using the docker version as per instructions
    docker run --rm -v "$PWD:/data" minlag/mermaid-cli:latest -o "/data/$image_file" -i "/data/$mermaid_file" -t neutral -C "/data/.render-md-mermaid.css" -c "/data/.render-md-mermaid-config.json" -s 4
    
    if [[ "$image_file" =~ ^.*\.svg$ ]]; then
        # Fix for <br> tags in SVGs which often break XML parsing in browsers
        sed -i 's/<br>/<br\/>/g' "$image_file"
    fi
    rm "$mermaid_file"
done

rm .render-md-mermaid-config.json .render-md-mermaid.css
