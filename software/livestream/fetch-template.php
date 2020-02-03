#!/usr/bin/env php
<?php

$ch = curl_init();
curl_setopt($ch, CURLOPT_URL, 'https://fosdem.org/searcher/layout.rhtml');
curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);

$template = curl_exec($ch);
curl_close($ch);

$template = preg_replace('/href="\//', 'href="https://fosdem.org/', $template);
$template = preg_replace('/action="\//', 'action="https://fosdem.org/', $template);
$template = preg_replace('/fosdem-.*\.css/', 'fosdem-static.css', $template);

$placeholders = [
	'@head' => '{% block head %}{% endblock head %}',
	'@title' => '{{ title }}',
	'@q' => null,
	'yield' => '{% block content %}{% endblock content %}',
];

foreach ($placeholders as $placeholder => $replacement) {
	$template = preg_replace('/<%=\ ?' . $placeholder . '\ ?%>/', $replacement, $template);
}

file_put_contents(__DIR__ . '/view/layout.fosdem.twig', $template);

echo 'Template saved to layout.fosdem.twig' . "\n";

