const puppeteer = require('puppeteer');
const path = require('path');

(async () => {
  try {
    const browser = await puppeteer.launch({
      executablePath: 'C:/Program Files/Google/Chrome/Application/chrome.exe',
      args: ['--no-sandbox', '--disable-setuid-sandbox'],
      headless: true,
    });
    const page = await browser.newPage();
    const fileUrl = 'file://' + path.resolve('3_Work_Experience/3_3_Study_Notes/life_math_7_questions_render.html');
    await page.goto(fileUrl, {waitUntil: 'networkidle2'});
    await page.waitForFunction(() => window.MathJax && window.MathJax.typesetPromise, {timeout: 10000});
    await page.evaluate(() => window.MathJax.typesetPromise());

    const ids = ['example27', 'example28'];
    for (const id of ids) {
      const element = await page.$(`#${id}`);
      if (!element) {
        throw new Error(`Element #${id} not found`);
      }
      const output = path.resolve(`3_Work_Experience/3_3_Study_Notes/life_math_7_${id}.png`);
      await element.screenshot({path: output});
      console.log('saved', output);
    }

    await browser.close();
  } catch (err) {
    console.error(err);
    process.exit(1);
  }
})();